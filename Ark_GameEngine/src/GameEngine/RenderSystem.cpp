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

	CreateDevice();

	CreateSwapChain();

	CreateRenderTgtView();

	SetViewPort();

	MessageBox(NULL, L"DirectX11 Initialised", L"DirectX11 Initialised", 0);
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

	return true;
}

bool RenderSystem::SetViewPort() {



	return true;
}

// Update Stage
int RenderSystem::Update()
{
	MessageBox(NULL, L"DirectX11 Frame", L"DirectX11 Frame", 0);
	return 0;
}

// Release Stage
int RenderSystem::Release()
{
	MessageBox(NULL, L"DirectX11 Shutdown", L"DirectX11 Shutdown", 0);
	return 0;
}

void RenderSystem::SetHWND(HWND windowHWND)
{
	m_tgtWindow = windowHWND;
}




