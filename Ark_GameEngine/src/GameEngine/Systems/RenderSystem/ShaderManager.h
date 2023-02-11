#pragma once
#include <vector>
#include <d3d11.h>
#include <d3d11_2.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <string>

namespace Ark {
	class ShaderManager {

	public:
		ShaderManager();

		bool SetShaderPath(std::wstring shaderFolder);

		bool CompileVertexShader(
			std::wstring shaderFileName, 
			Microsoft::WRL::ComPtr<ID3D11Device> &d3dDevice,
			bool textureLayout,
			std::string entryPoint = "Basic_VS");

		bool CompilePixelShader(std::wstring shaderFileName, Microsoft::WRL::ComPtr<ID3D11Device> &d3dDevice, std::string entryPoint = "Basic_PS");

		ID3D11VertexShader* GetVtxShader(unsigned int shaderPos = 0);
		ID3D11PixelShader* GetPxlShader(unsigned int shaderPos = 0);
		ID3D11InputLayout* GetInputLayout(unsigned int layoutPos = 0);

	private:
		std::vector<Microsoft::WRL::ComPtr<ID3D11VertexShader>> m_vertexShaders;
		std::vector<Microsoft::WRL::ComPtr<ID3D11PixelShader>> m_pixelShaders;

		std::vector<Microsoft::WRL::ComPtr<ID3D11InputLayout>> m_inputLayouts;		
	
		std::wstring m_shaderFolder;

		bool CreateInputLayout(
			Microsoft::WRL::ComPtr<ID3DBlob> &vtxShaderBlob, 
			Microsoft::WRL::ComPtr<ID3D11Device>& d3dDevice, 
			bool isTextureLayout = false);
	};
}
