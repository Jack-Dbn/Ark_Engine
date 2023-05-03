#include "GraphicsSystem.h"

// Constructor
GraphicsSystem::GraphicsSystem()
{
}

// Initialise Stage
int GraphicsSystem::Initialise(bool* isGameRunning)
{
	//Check there is a window to render to.
	if (m_tgtWindow == NULL) {
		return -1;
	}

	//Check shader manage has path to shaders.
	if (!m_shaderManager.SetShaderPath(m_assetFolderPath + L"Shaders/")) {
		return -2;
	}

	//Create D3D11 Device & Device Context
	CreateDevice();

	//Create Swap chain
	CreateSwapChain();	

	//Create Render Target View
	CreateRenderTgtView();

	//Create Depth Stencil View
	D3D11_TEXTURE2D_DESC backBufferDesc = GetBackBufferDesc();
	CreateDepthStencilVw(backBufferDesc);

	//Create Sampler
	CreateSampler();

	//Create Constant Buffer
	CreateConstBuffer();

	//Update pipeline buffer with camera matrices.
	m_constantBufferData.m_proj = m_camera.GetProjectionMatrix(static_cast<float>(backBufferDesc.Height), static_cast<float>(backBufferDesc.Width));
	m_constantBufferData.m_view = m_camera.GetViewMatrix();

	//Set viewport
	SetViewPort(backBufferDesc.Width, backBufferDesc.Height);

	//Compile Shaders
	bool compileSuccess = m_shaderManager.CompileVertexShader(L"Basic_VS.hlsl", m_d3dDevice);
	compileSuccess = compileSuccess && m_shaderManager.CompilePixelShader(L"Colour_PS.hlsl", m_d3dDevice, "Colour_PS");

	//Return error code if compile is unsuccessful.
	if (!compileSuccess) {
		return -3;
	}

	return 0;
}

bool GraphicsSystem::CreateDevice()
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

	//Store device & context in class.
	newD3dDevice.As(&m_d3dDevice);
	newD3dDeviceContext.As(&m_d3dDeviceContext);

	if (m_d3dDevice == nullptr || m_d3dDeviceContext == nullptr) {
		return false;
	}

	return true;
}

bool GraphicsSystem::CreateSwapChain()
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

	//Create swap chain and assign it to window.
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

bool GraphicsSystem::CreateRenderTgtView()
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	HRESULT getbufferRes = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

	if (FAILED(getbufferRes)) {
			return false;
	}

	HRESULT createRtvRes = m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_renderTgtView);

	if (FAILED(createRtvRes)) {
		return false;
	}	

	return true;
}

//Ensures objects are rendered at correct depths, e.g. object behind another object is obscured.
bool GraphicsSystem::CreateDepthStencilVw(D3D11_TEXTURE2D_DESC backBufferDesc)
{

	//Depth Stencil Desc
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Height = backBufferDesc.Height;
	depthStencilDesc.Width = backBufferDesc.Width;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencil;
	HRESULT res = m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencil);

	if (FAILED(res)) {
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC dpthStencilVwDesc;
	dpthStencilVwDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dpthStencilVwDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dpthStencilVwDesc.Flags = 0;
	dpthStencilVwDesc.Texture2D.MipSlice = 0;

	res = m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &dpthStencilVwDesc, &m_depthStencilView);

	if (FAILED(res)) {
		return false;
	}

	return true;
}

bool GraphicsSystem::CreateConstBuffer()
{
	D3D11_BUFFER_DESC constBufferDesc = { 0 };
	constBufferDesc.ByteWidth = sizeof(m_constantBufferData);
	constBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constBufferDesc.CPUAccessFlags = 0;
	constBufferDesc.MiscFlags = 0;
	constBufferDesc.StructureByteStride = 0;

	HRESULT res = m_d3dDevice->CreateBuffer(&constBufferDesc, nullptr, &m_constantBuffer);

	if (FAILED(res)) {
		return false;
	}

	return true;
}

bool GraphicsSystem::CreateSampler()
{
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	//No anisotropic filtering so ignored.
	samplerDesc.MaxAnisotropy = 0;

	//Specify how tex coords beyond boundaries are handled.
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	//No Mip clamping or bias
	samplerDesc.MipLODBias = 0.0f;

	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//No comp functoion
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

	//Border address mode is not used so this is ignored.
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;

	HRESULT res = m_d3dDevice->CreateSamplerState(&samplerDesc, &m_sampler);

	if (FAILED(res)) {
		MessageBoxA(NULL, "Sampler Creation Error", "Sampler Creation Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsSystem::SetViewPort(float viewPortWidth, float viewPortHeight) {

	D3D11_VIEWPORT newViewPort;

	newViewPort.TopLeftX = 0.0f;
	newViewPort.TopLeftY = 0.0f;
	newViewPort.Width = viewPortWidth;
	newViewPort.Height = viewPortHeight;
	newViewPort.MinDepth = D3D11_MIN_DEPTH;
	newViewPort.MaxDepth = D3D11_MAX_DEPTH;

	m_d3dDeviceContext->RSSetViewports(1, &newViewPort);
}

D3D11_TEXTURE2D_DESC GraphicsSystem::GetBackBufferDesc()
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	HRESULT getbufferRes = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

	D3D11_TEXTURE2D_DESC backBufferDesc = { 0 };
	backBuffer->GetDesc(&backBufferDesc);

	return backBufferDesc;
}

void GraphicsSystem::SetupFrame(float redVal, float greenVal, float blueVal, float alphaVal)
{
	m_d3dDeviceContext->OMSetRenderTargets(1, m_renderTgtView.GetAddressOf(), m_depthStencilView.Get());

	//Set background colour of scene.
	float backgrndColour[4] = { redVal, greenVal, blueVal, alphaVal };
	m_d3dDeviceContext->ClearRenderTargetView(m_renderTgtView.Get(), backgrndColour);
	m_d3dDeviceContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	//Set up constant buffer.
	D3D11_TEXTURE2D_DESC backBufferDesc = GetBackBufferDesc();
	m_constantBufferData.m_proj = m_camera.GetProjectionMatrix(static_cast<float>(backBufferDesc.Height), static_cast<float>(backBufferDesc.Width));
	m_constantBufferData.m_view = m_camera.GetViewMatrix();
}

// Update Stage
int GraphicsSystem::Update(Ark::ComponentManager& engineCM)
{	
	//Initialise frame ready for drawing.
	SetupFrame();
	
	//Iterate through compatible entities.
	for (int i = 0; i < m_EntityList.size(); i++) {
		//Note entity id.
		Ark::Entity entityIn = m_EntityList[i];

		//Get transform of entity.
		Ark::Transform entityTransform;
		engineCM.GetComponent<Ark::Transform>(entityIn, entityTransform);

		//Replace old model matrix with entity's.
		m_constantBufferData.m_model = entityTransform.GetModelMtx();

		//Get material of entity.
		Ark::Material entityMaterial;
		engineCM.GetComponent<Ark::Material>(entityIn, entityMaterial);

		//Get model of entity.
		Ark::Model entityModel;
		engineCM.GetComponent<Ark::Model>(entityIn, entityModel);

		//Check model is ready to be rendered before drawing.
		if (!entityModel.m_RenderReady) {
			continue;
		}	
		
		//Render entity onto pending frame.
		DrawEntity(entityModel, entityMaterial);		
	}

	//Send frame to window.
	PresentFrame(true);

	return 0;
}

bool GraphicsSystem::DrawEntity(Ark::Model &tgtModel, Ark::Material &tgtMaterial)
{	
	//Create pointers to the shaders and input layout.
	ID3D11VertexShader* eVtxShader = m_shaderManager.GetVtxShader(tgtModel.GetVtxShaderId());
	ID3D11PixelShader* ePxlShader = m_shaderManager.GetPxlShader(tgtMaterial.GetPxlShaderId());
	ID3D11InputLayout* eInpLayout = m_shaderManager.GetInputLayout(tgtModel.GetVtxShaderId());

	//Number of bytes between vertices.
	UINT stride = sizeof(Ark::vertex);
	//Number of bytes from start of the buffer to first vertex.
	UINT offset = 0;

	//Load constant buffer (pipeline buffer)
	m_d3dDeviceContext->UpdateSubresource(m_constantBuffer.Get(), 0, nullptr, &m_constantBufferData, 0, 0);

	//Set buffers and input layout.
	m_d3dDeviceContext->IASetInputLayout(eInpLayout);
	m_d3dDeviceContext->IASetVertexBuffers(0, 1, tgtModel.GetVtxBufferAddr(), &stride, &offset);
	m_d3dDeviceContext->IASetIndexBuffer(tgtModel.GetIdxBuffer(), DXGI_FORMAT_R32_UINT, 0);

	//Set draw method.
	m_d3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Set vertex shader.
	m_d3dDeviceContext->VSSetShader(eVtxShader, nullptr, 0);
	m_d3dDeviceContext->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());

	//Set pixel shader.
	m_d3dDeviceContext->PSSetShader(ePxlShader, nullptr, 0);
	m_d3dDeviceContext->PSSetShaderResources(0, 1, tgtMaterial.GetTextureView().GetAddressOf());
	m_d3dDeviceContext->PSSetSamplers(0, 1, m_sampler.GetAddressOf());

	//Render entity.
	m_d3dDeviceContext->DrawIndexed(tgtModel.GetIdxCount(), 0, 0);

	return true;
}

//Display frame on window.
bool GraphicsSystem::PresentFrame(bool vSyncOn)
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
int GraphicsSystem::Release()
{
	//MessageBox(NULL, L"DirectX11 Shutdown", L"DirectX11 Shutdown", 0);
	return 0;
}

bool GraphicsSystem::Resize(int newHeight, int newWidth)
{
	//Ensure swap chain exists before attempting resize.
	if (m_swapChain) {

		m_depthStencilView.Reset();
		m_renderTgtView.Reset();		

		//Resize swapchain's buffers.
		HRESULT resizeRes = m_swapChain->ResizeBuffers(2, 0, 0, DXGI_FORMAT_B8G8R8A8_UNORM, 0);

		if (FAILED(resizeRes)) {
			return false;
		}

		D3D11_TEXTURE2D_DESC backBufferDesc = GetBackBufferDesc();

		bool a = CreateRenderTgtView();
		a = a && CreateDepthStencilVw(backBufferDesc);

		SetViewPort(static_cast<float>(newWidth), static_cast<float>(newHeight));

		//Readjust projection matrix as there will be a new aspect ratio.
		m_constantBufferData.m_proj = m_camera.GetProjectionMatrix(static_cast<float>(backBufferDesc.Height), static_cast<float>(backBufferDesc.Width));

		return true;
	}

	return false;
}

void GraphicsSystem::SetParam(HWND windowHWND, std::wstring assetFolderPath)
{
	m_tgtWindow = windowHWND;
	m_assetFolderPath = assetFolderPath;
}

Ark::Camera* GraphicsSystem::GetCamera()
{
	return &m_camera;
}

//Material & model methods need to go via graphics system for d3d device.
Ark::Model GraphicsSystem::CreateDxModelEx(void* vtxArray, unsigned int vtxArraySize, unsigned int* idxArray, unsigned int idxArraySize)
{
	Ark::Model newModel;

	newModel.SetMeshEx(vtxArray, vtxArraySize, idxArray, idxArraySize, m_d3dDevice);

	return newModel;
}

Ark::Model GraphicsSystem::CreateDxModel(std::string filePath, bool CwWindingDir, bool LH_Convert)
{
	Ark::Model newModel;

	newModel.SetMeshFromFile(filePath, m_d3dDevice, CwWindingDir, LH_Convert);

	return newModel;
}

Ark::Material GraphicsSystem::CreateMaterial(std::wstring textureFilePath)
{
	Ark::Material newMaterial;

	newMaterial.AddTextureDDS(m_d3dDevice, textureFilePath);

	return newMaterial;
}




