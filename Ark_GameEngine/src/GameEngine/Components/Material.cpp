#include "Material.h"

Ark::Material::Material(unsigned int tgtShaderID, vector3D tgtColour, std::string textureFilePath)
{
	m_rgbColour = tgtColour;
	m_pixelShader = tgtShaderID;
}

unsigned int Ark::Material::GetPxlShaderId()
{
	return m_pixelShader;
}
