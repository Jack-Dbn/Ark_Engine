#pragma once
#include "..\..\Math.h"

namespace Ark {
	class Camera
	{
	public:
		Camera();

		Ark::matrix4x4 GetProjectionMatrix(float windowHeight, float windowWidth);
		Ark::matrix4x4 GetViewMatrix();

		void Translate(float x = 0.0f, float y = 0.0f, float z = 0.0f);
		void Rotate(float pitch = 0.0f, float yaw = 0.0f);

	private:
		//Camera pitch and yaw
		float m_pitch, m_yaw;

		//Camera position
		Ark::vector3D m_position;
		Ark::vector3D m_deltaPosition;

		//Camera's field of view
		float m_fov;

		//Camera clipping planes
		float m_nearClipPlane, m_farClipPlane;
	};
}

