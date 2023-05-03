#pragma once
#include <Windows.h>
#include <string>
#include "../Math.h"

namespace Ark {
	class Transform
	{
	public:
		Transform();
		Transform(float x, float y, float z);

		void SetPosition(float x = 0, float y = 0, float z = 0);
		void SetOrientation(float x = 0, float y = 0, float z = 0);
		void SetScale(float x = 1.0, float y = 1.0, float z = 1.0);

		void Translate(float x = 0, float y = 0, float z = 0);
		void Rotate(float x = 0, float y = 0, float z = 0);
		void Resize(float x = 0, float y = 0, float z = 0);

		Ark::matrix4x4 GetModelMtx();
		Ark::vector3D GetPos();

	private:
		bool UpdateTransformMtx();

		float m_posX, m_posY, m_posZ;
		float m_rotationX, m_rotationY, m_rotationZ;
		float m_scaleX, m_scaleY, m_scaleZ;

		Ark::matrix4x4 m_transformMtx;
	};
}


