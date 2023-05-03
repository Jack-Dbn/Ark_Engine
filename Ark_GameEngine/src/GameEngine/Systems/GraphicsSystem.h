#pragma once
#include <d3d11.h>
#include <d3d11_2.h>
#include <Windows.h>
#include <wrl.h>
#include <vector>
#include <string>
#include "../System.h"
#include "GraphicsSystem/ShaderManager.h"
#include "GraphicsSystem/ConstantBuffer.h"
#include "GraphicsSystem/Camera.h"


class GraphicsSystem : public System
{
public:
	GraphicsSystem();

	//System stages
	int Initialise(bool* isGameRunning);
	int Update(Ark::ComponentManager& engineCM);
	int Release();

	//App Event
	bool Resize(int newHeight, int newWidth);

	//Getters & Setters
	void SetParam(HWND windowHWND, std::wstring assetFolderPath);
	Ark::Camera* GetCamera();

	//Create model and material objects for user.
	Ark::Model CreateDxModelEx(
		void* vtxArray,
		unsigned int vtxArraySize,
		unsigned int* idxArray,
		unsigned int idxArraySize);

	Ark::Model CreateDxModel(std::string filePath, bool CwWindingDir = false, bool LH_Convert = true);

	Ark::Material CreateMaterial(std::wstring textureFilePath);

private:
	//Init - D3D11
	bool CreateDevice();
	bool CreateSwapChain();
	bool CreateRenderTgtView();
	bool CreateDepthStencilVw(D3D11_TEXTURE2D_DESC backBufferDesc);
	bool CreateConstBuffer();
	bool CreateSampler();
	void SetViewPort(float viewPortWidth = 1920.0f, float viewPortHeight = 1080.0f);

	//Util
	D3D11_TEXTURE2D_DESC GetBackBufferDesc();

	//Update

	//Draw backdrop
	void SetupFrame(const float redVal = 0.66f, const float greenVal = 0.73f, const float blueVal = 0.75f, const float alphaVal = 1.0f);

	//Draw entity
	bool DrawEntity(Ark::Model& tgtModel, Ark::Material& tgtMaterial);

	//Present frame with drawn entities.
	bool PresentFrame(bool vSyncOn = true);	

	//Stores window handle
	HWND m_tgtWindow = NULL;
	//Stores directory with models/textures/shaders
	std::wstring m_assetFolderPath = L"";

	//D3D11 Objects
	Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dDeviceContext;

	Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTgtView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;
	//Pipeline Buffer
	Ark::ConstantBuffer m_constantBufferData;

	//Cameras
	Ark::Camera m_camera;

	Ark::ShaderManager m_shaderManager;
};