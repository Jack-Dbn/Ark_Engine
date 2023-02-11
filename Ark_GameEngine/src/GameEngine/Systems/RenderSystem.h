#pragma once
#include <d3d11.h>
#include <d3d11_2.h>
#include <Windows.h>
#include <wrl.h>
#include <vector>
#include <string>
#include "../System.h"
#include "RenderSystem/ShaderManager.h"
#include "../Math.h"


class RenderSystem : public System
{
public:
	RenderSystem();

	int Initialise();
	int Update(Ark::ComponentManager& engineCM);
	int Release();

	bool Resize(int newHeight, int newWidth);

	//Getters & Setters
	void SetParam(HWND windowHWND, std::wstring assetFolderPath);

	Ark::Model CreateDxModel(
		void* vtxArray,
		unsigned int vtxArraySize,
		unsigned int* idxArray,
		unsigned int idxArraySize);

private:
	//Init
	bool CreateDevice();
	bool CreateSwapChain();
	bool CreateRenderTgtView();
	void SetViewPort(float viewPortWidth = 1920.0f, float viewPortHeight = 1080.0f);

	//Update
	void SetupFrame(const float redVal = 0.0f, const float greenVal = 0.75f, const float blueVal = 0.75f, const float alphaVal = 1.0f);
	bool DrawEntity(Ark::Model& tgtModel, Ark::Material& tgtMaterial);
	bool PresentFrame(bool vSyncOn = true);	

	HWND m_tgtWindow = NULL;
	std::wstring m_assetFolderPath = L"";

	Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dDeviceContext;

	Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTgtView;

	Ark::ShaderManager m_shaderManager;
};