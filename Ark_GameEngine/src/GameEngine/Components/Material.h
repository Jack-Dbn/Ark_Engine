#pragma once
#include <Windows.h>
#include <string>
#include "..\Component.h"

namespace Ark {
	class Material : Component
	{
	public:
		Material(unsigned int tgtShaderID = 0, vector3D tgtColour = vector3D(128.0f, 128.0f, 128.0f), std::string textureFilePath = "");

		unsigned int GetPxlShaderId();

	private:

		vector3D m_rgbColour;
		unsigned int m_pixelShader;
	};
}

