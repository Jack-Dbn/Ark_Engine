#include "Material.h"

Ark::Material::Material(unsigned int tgtShaderID)
{
	m_pixelShader = tgtShaderID;

}

bool Ark::Material::AddTextureDDS(Microsoft::WRL::ComPtr<ID3D11Device>& d3dDevice, std::wstring textureFilePath)
{	
	//Create placeholder for texture resource
	Microsoft::WRL::ComPtr<ID3D11Resource> textureResouce;

	//Create texture view.
	HRESULT res = DirectX::CreateDDSTextureFromFile(d3dDevice.Get(), textureFilePath.c_str(), textureResouce.GetAddressOf(), m_textureView.GetAddressOf());

	//Check to ensure creating texture hasnt failed.
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
