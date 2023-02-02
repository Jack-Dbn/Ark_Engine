#pragma once
#include <vector>
#include <d3d11.h>
#include <d3d11_2.h>
#include <wrl.h>
#include <string>

namespace Ark {
	class ShaderManager {

	public:
		ShaderManager();

		bool SetShaderPath(std::wstring shaderFolder);

	private:
		std::vector<Microsoft::WRL::ComPtr<ID3D11VertexShader>> m_vertexShaders;
		std::vector<Microsoft::WRL::ComPtr<ID3D11PixelShader>> m_pixelShaders;
	
		LPCWSTR m_shaderFolder;
	};
}