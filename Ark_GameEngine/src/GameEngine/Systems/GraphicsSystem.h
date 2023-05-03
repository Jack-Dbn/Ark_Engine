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
//GUI
#include "../include/ImGui/imgui.h"
#include "../include/ImGui/imgui_impl_win32.h"
#include "../include/ImGui/imgui_impl_dx11.h"

class GraphicsSystem : public System
{
public:
	GraphicsSystem();

	int Initialise(bool* isGameRunning);
	int Update(Ark::ComponentManager& engineCM);
	int Release();

	bool Resize(int newHeight, int newWidth);

	//Getters & Setters
	void SetParam(HWND windowHWND, std::wstring assetFolderPath);
	Ark::Camera* GetCamera();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	Ark::Model CreateDxModelEx(
		void* vtxArray,
		unsigned int vtxArraySize,
		unsigned int* idxArray,
		unsigned int idxArraySize);

	Ark::Model CreateDxModel(std::string filePath, bool CwWindingDir = false, bool LH_Convert = true);

	Ark::Material CreateMaterial(std::wstring textureFilePath);

private:
	//Init
	bool CreateDevice();
	bool CreateSwapChain();
	bool CreateRenderTgtView();
	bool CreateDepthStencilVw(D3D11_TEXTURE2D_DESC backBufferDesc);
	bool CreateConstBuffer();
	bool CreateSampler();
	void SetViewPort(float viewPortWidth = 1920.0f, float viewPortHeight = 1080.0f);

	D3D11_TEXTURE2D_DESC GetBackBufferDesc();

	//Update
	void SetupFrame(const float redVal = 0.66f, const float greenVal = 0.73f, const float blueVal = 0.75f, const float alphaVal = 1.0f);
	bool DrawEntity(Ark::Model& tgtModel, Ark::Material& tgtMaterial);
	bool PresentFrame(bool vSyncOn = true);	

	HWND m_tgtWindow = NULL;
	std::wstring m_assetFolderPath = L"";

	Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dDeviceContext;

	Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTgtView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;
	Ark::ConstantBuffer m_constantBufferData;

	//Cameras
	Ark::Camera m_camera;

	Ark::ShaderManager m_shaderManager;

	//Simply to rotate model until input is added.
	float m_tempDegVar = 0.0f;
};