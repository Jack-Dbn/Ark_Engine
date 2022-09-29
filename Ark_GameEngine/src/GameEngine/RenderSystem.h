#pragma once
#include "System.h"
#include <d3d11.h>
#include <d3d11_2.h>
#include <Windows.h>
#include <wrl.h>


class RenderSystem : public System
{
public:
	RenderSystem();

	int Initialise();
	int Update();
	int Release();

	//Getters & Setters
	void SetHWND(HWND windowHWND);

private:
	bool CreateDevice();
	bool CreateSwapChain();
	bool CreateRenderTgtView();
	bool SetViewPort();

	HWND m_tgtWindow = NULL;

	Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dDeviceContext;

	Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTgtView;
};

