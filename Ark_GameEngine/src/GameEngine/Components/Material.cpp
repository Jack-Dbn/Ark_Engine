#include "Material.h"

Ark::Material::Material(vector3D tgtColour, int tgtShaderID)
{
	m_rgbColour = tgtColour;
	m_pixelShader = tgtShaderID;
}
