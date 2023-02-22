#include "Material.h"

Ark::Material::Material(unsigned int tgtShaderID)
{
	m_pixelShader = tgtShaderID;

}

bool Ark::Material::AddTextureDDS(Microsoft::WRL::ComPtr<ID3D11Device>& d3dDevice, std::wstring textureFilePath)
{	
	Microsoft::WRL::ComPtr<ID3D11Resource> textureResouce;

	HRESULT res = DirectX::CreateDDSTextureFromFile(d3dDevice.Get(), textureFilePath.c_str(), textureResouce.GetAddressOf(), m_textureView.GetAddressOf());

	if (FAILED(res)) {
		MessageBoxA(NULL, "DDS Texture Creation Error", "DDS Texture Creation Error", MB_OK);
		return false;
	}

	return true;
}

unsigned int Ark::Material::GetPxlShaderId()
{
	return m_pixelShader;
}

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Ark::Material::GetTextureView()
{
	return m_textureView;
}
