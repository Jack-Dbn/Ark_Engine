#pragma once
#include <Windows.h>
#include <string>
#include "..\Component.h"

namespace Ark {
	class Material : Component
	{
	public:
		Material(vector3D tgtColour = vector3D(128.0f, 128.0f, 128.0f), int tgtShaderID = 0);

	private:
		vector3D m_rgbColour;
		int m_pixelShader;
	};
}

