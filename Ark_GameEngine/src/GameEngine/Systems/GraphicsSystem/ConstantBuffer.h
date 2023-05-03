#pragma once
#include <d3d11.h>
#include "..\..\Math.h"

namespace Ark {
	//Pipeline Buffer
	class ConstantBuffer
	{
	public:
		Ark::matrix4x4 m_model;
		Ark::matrix4x4 m_view;
		Ark::matrix4x4 m_proj;
	};
}

