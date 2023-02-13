#include "RenderSystem.h"

// Constructor
RenderSystem::RenderSystem()
{
}

// Initialise Stage
int RenderSystem::Initialise()
{
	if (m_tgtWindow == NULL) {
		return -1;
	}

	if (!m_shaderManager.SetShaderPath(m_assetFolderPath + L"Shaders/")) {
		return -2;
	}

	CreateDevice();

	CreateSwapChain();

	CreateRenderTgtView();	

	bool compileSuccess = m_shaderManager.CompileVertexShader(L"Basic_VS.hlsl", m_d3dDevice, false);
	compileSuccess = compileSuccess && m_shaderManager.CompilePixelShader(L"Colour_PS.hlsl", m_d3dDevice, "Colour_PS");

	if (!compileSuccess) {
		return -3;
	}

	//MessageBox(NULL, L"DirectX11 Initialised", L"DirectX11 Initialised", 0);
	return 0;
}

bool RenderSystem::CreateDevice()
{
	//For direct2d support
	UINT createFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	//Order of levels directx will attempt to create.
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_1
	};

	Microsoft::WRL::ComPtr<ID3D11Device> newD3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> newD3dDeviceContext;

	HRESULT createResult = D3D11CreateDevice(
		nullptr, 
		D3D_DRIVER_TYPE_HARDWARE, 
		nullptr, 
		createFlags, 
		featureLevels, 
		ARRAYSIZE(featureLevels), 
		D3D11_SDK_VERSION, &newD3dDevice, 
		nullptr, 
		&newD3dDeviceContext);

	if (FAILED(createResult)) {
		return false;
	}

	newD3dDevice.As(&m_d3dDevice);
	newD3dDeviceContext.As(&m_d3dDeviceContext);

	if (m_d3dDevice == nullptr || m_d3dDeviceContext == nullptr) {
		return false;
	}

	return true;
}

bool RenderSystem::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
	swapChainDesc.Stereo = false;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.Scaling = DXGI_SCALING_NONE;
	swapChainDesc.Flags = 0;

	//Automatically determine size
	swapChainDesc.Width = 0;
	swapChainDesc.Height = 0;

	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;

	//No Multi Sampling
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	//Flip effect
	swapChainDesc.BufferCount = 2;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;

	
	Microsoft::WRL::ComPtr<IDXGIDevice2> dxgiDevice;
	m_d3dDevice.As(&dxgiDevice);

	dxgiDevice->SetMaximumFrameLatency(1);
	
	Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
	dxgiDevice->GetAdapter(&dxgiAdapter);

	Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory;
	dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

	HRESULT swpChnResult = dxgiFactory->CreateSwapChainForHwnd(
		m_d3dDevice.Get(),
		m_tgtWindow,
		&swapChainDesc,
		NULL,
		nullptr,
		&m_swapChain);

	if (FAILED(swpChnResult)) {
		return false;
	}

	return true;
}

bool RenderSystem::CreateRenderTgtView()
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	HRESULT getbufferRes = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

	if (FAILED(getbufferRes)) {
			return false;
	}

	HRESULT createRtvRes = m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_RenderTgtView);

	if (FAILED(createRtvRes)) {
		return false;
	}

	D3D11_TEXTURE2D_DESC backBufferDesc = { 0 };
	backBuffer->GetDesc(&backBufferDesc);

	SetViewPort(backBufferDesc.Width, backBufferDesc.Height);

	return true;
}

void RenderSystem::SetViewPort(float viewPortWidth, float viewPortHeight) {

	D3D11_VIEWPORT newViewPort;

	newViewPort.TopLeftX = 0.0f;
	newViewPort.TopLeftY = 0.0f;
	newViewPort.Width = viewPortWidth;
	newViewPort.Height = viewPortHeight;
	newViewPort.MinDepth = D3D11_MIN_DEPTH;
	newViewPort.MaxDepth = D3D11_MAX_DEPTH;

	m_d3dDeviceContext->RSSetViewports(1, &newViewPort);
}

void RenderSystem::SetupFrame(float redVal, float greenVal, float blueVal, float alphaVal)
{
	float backgrndColour[4] = { redVal, greenVal, blueVal, alphaVal };
	m_d3dDeviceContext->ClearRenderTargetView(m_RenderTgtView.Get(), backgrndColour);

	m_d3dDeviceContext->OMSetRenderTargets(1, m_RenderTgtView.GetAddressOf(), NULL);		
}

// Update Stage
int RenderSystem::Update(Ark::ComponentManager& engineCM)
{
	SetupFrame();
		
	for (int i = 0; i < m_EntityList.size(); i++) {
		Ark::Entity entityIn = m_EntityList[i];

		Ark::Transform entityTransform;
		engineCM.GetComponent<Ark::Transform>(entityIn, entityTransform);

		Ark::Material entityMaterial;
		engineCM.GetComponent<Ark::Material>(entityIn, entityMaterial);

		Ark::Model entityModel;
		engineCM.GetComponent<Ark::Model>(entityIn, entityModel);

		if (!entityModel.m_RenderReady) {
			continue;
		}	
							
		DrawEntity(entityModel, entityMaterial);		
	}

	PresentFrame(true);
	//MessageBox(NULL, L"DirectX11 Frame", L"DirectX11 Frame", 0);
	return 0;
}

bool RenderSystem::DrawEntity(Ark::Model &tgtModel, Ark::Material &tgtMaterial)
{	
	ID3D11VertexShader* eVtxShader = m_shaderManager.GetVtxShader(tgtModel.GetVtxShaderId());
	ID3D11PixelShader* ePxlShader = m_shaderManager.GetPxlShader(tgtMaterial.GetPxlShaderId());
	ID3D11InputLayout* eInpLayout = m_shaderManager.GetInputLayout(tgtModel.GetVtxShaderId());

	//Draw Entity
	UINT stride = sizeof(Ark::vertex);
	UINT offset = 0;

	m_d3dDeviceContext->IASetInputLayout(eInpLayout);

	m_d3dDeviceContext->IASetVertexBuffers(0, 1, tgtModel.GetVtxBufferAddr(), &stride, &offset);

	m_d3dDeviceContext->IASetIndexBuffer(tgtModel.GetIdxBuffer(), DXGI_FORMAT_R32_UINT, 0);

	m_d3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_d3dDeviceContext->VSSetShader(eVtxShader, nullptr, 0);

	m_d3dDeviceContext->PSSetShader(ePxlShader, nullptr, 0);

	m_d3dDeviceContext->DrawIndexed(tgtModel.GetIdxCount(), 0, 0);

	return true;
}

bool RenderSystem::PresentFrame(bool vSyncOn)
{
	int syncInterval = 0;
	if (vSyncOn) {
		syncInterval = 1;
	}

	HRESULT presentRes = m_swapChain->Present(syncInterval, 0);

	if (FAILED(presentRes)) {
		return false;
	}

	return true;
}

// Release Stage
int RenderSystem::Release()
{
	//MessageBox(NULL, L"DirectX11 Shutdown", L"DirectX11 Shutdown", 0);
	return 0;
}

bool RenderSystem::Resize(int newHeight, int newWidth)
{
	if (m_swapChain) {

		m_RenderTgtView.Reset();

		HRESULT resizeRes = m_swapChain->ResizeBuffers(2, 0, 0, DXGI_FORMAT_B8G8R8A8_UNORM, 0);

		if (FAILED(resizeRes)) {
			return false;
		}

		bool a = CreateRenderTgtView();

		return true;
	}

	return false;
}

void RenderSystem::SetParam(HWND windowHWND, std::wstring assetFolderPath)
{
	m_tgtWindow = windowHWND;
	m_assetFolderPath = assetFolderPath;
}

Ark::Model RenderSystem::CreateDxModel(void* vtxArray, unsigned int vtxArraySize, unsigned int* idxArray, unsigned int idxArraySize)
{
	Ark::Model newModel;

	newModel.SetMeshManual(vtxArray, vtxArraySize, idxArray, idxArraySize, m_d3dDevice);

	return newModel;
}




