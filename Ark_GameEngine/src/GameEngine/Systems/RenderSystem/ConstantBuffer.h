#pragma once
#include <d3d11.h>
#include "..\..\Math.h"

namespace Ark {
	class ConstantBuffer
	{
	public:
		Ark::matrix4x4 m_model;
		Ark::matrix4x4 m_view;
		Ark::matrix4x4 m_proj;

		bool SetDefaults();

		bool setFov(D3D11_TEXTURE2D_DESC bufferDesc, float fovDeg = 70.0f);
	};
}

