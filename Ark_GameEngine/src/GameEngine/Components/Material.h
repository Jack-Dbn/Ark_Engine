#pragma once
#include <Windows.h>
#include <string>
#include <wrl.h>
#include <d3d11.h>
#include <d3d11_2.h>
#include "..\Component.h"
#include "..\include\DDSTextureLoader11.h"

namespace Ark {
	class Material : Component
	{
	public:
		Material(unsigned int tgtShaderID = 0);

		//Init Texture Methods
		//bool AddTexture(Microsoft::WRL::ComPtr<ID3D11Device>& d3dDevice, std::wstring textureFilePath = L"");
		bool AddTextureDDS(Microsoft::WRL::ComPtr<ID3D11Device>& d3dDevice, std::wstring textureFilePath = L"");

		unsigned int GetPxlShaderId();
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTextureView();

	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureView;
		unsigned int m_pixelShader;
	};
}

