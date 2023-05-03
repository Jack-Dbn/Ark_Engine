#pragma once
#include <Windows.h>
#include <string>
#include <wrl.h>
#include <d3d11.h>
#include <d3d11_2.h>
#include "..\include\DDSTextureLoader11.h"

namespace Ark {
	class Material
	{
	public:
		//Default pixel shader index is 0.
		Material(unsigned int tgtShaderID = 0);

		//Init Texture Methods
		bool AddTextureDDS(Microsoft::WRL::ComPtr<ID3D11Device>& d3dDevice, std::wstring textureFilePath = L"");

		unsigned int GetPxlShaderId();

		//Getter allows pipeline to access texture view for rendering.
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTextureView();

	private:
		//D3D11 Object for storing texture data
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureView;

		//Index of pixel shader to use.
		unsigned int m_pixelShader;
	};
}

