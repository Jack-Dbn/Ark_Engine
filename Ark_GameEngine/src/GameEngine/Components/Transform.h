#pragma once
#include <Windows.h>
#include <string>
#include "..\Component.h"

namespace Ark {
	class Transform : public Component
	{
	public:
		Transform();

		void ChangePos(float x = 0, float y = 0, float z = 0);

		Ark::matrix4x4 GetModelMtx();

	private:
		float m_posX, m_posY, m_posZ;
		float m_rotationX, m_rotationY, m_rotationZ;
		float m_scaleX, m_scaleY, m_scaleZ;
	};
}


