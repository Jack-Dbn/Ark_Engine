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

	HWND tgtWindow = NULL;

	Microsoft::WRL::ComPtr<ID3D11Device> engineDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> engineDeviceContext;

	Microsoft::WRL::ComPtr<IDXGISwapChain1> engineSwapChain;
};

