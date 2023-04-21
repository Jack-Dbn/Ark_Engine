#include "Camera.h"

Ark::Camera::Camera()
{
	m_fov = 70.0f;

	m_nearClipPlane = 0.01f;
	m_farClipPlane = 100.0f;
}

Ark::matrix4x4 Ark::Camera::GetProjectionMatrix(float windowHeight, float windowWidth)
{
    //Initialise scaling factors.
    float yScale = 1.0f / (tan(m_fov / 2.0f));
    float xScale = 1.0f / (tan(m_fov / 2.0f));

    //Adjust scaling factors so they are in proportion with the window aspect ratio.
    if (windowWidth > windowHeight) {
        xScale = yScale * windowHeight / windowWidth;
    }
    else {
        yScale = xScale * windowWidth / windowHeight;
    }

    //Integrate clipping planes.
    float zScale = m_farClipPlane / (m_farClipPlane - m_nearClipPlane);

    //Create projection matrix.
    Ark::matrix4x4 projectionMatrix = {
        xScale, 0.0f, 0.0f, 0.0f,
        0.0f, yScale, 0.0f, 0.0f,
        0.0f, 0.0f, -zScale, -m_nearClipPlane * zScale,
        0.0f, 0.0f, -1.0f, 0.0f };

	return projectionMatrix;
}

Ark::matrix4x4 Ark::Camera::GetViewMatrix()
{
    Ark::matrix4x4 viewMatrix = {
        -1.0, 0.0f, 0.0f, 0.0f,
        0.0f, 0.89442718f, 0.44721359f, 0.0f,
        0.0f, 0.44721359f, -0.89442718f, -2.23606800f,
        0.0f, 0.0f, 0.0f, 1.0
    };

    //viewMatrix = TranslateMtx();//Need to pull static version from laptop.
    //viewMatrix = viewMatrix * RotateYmtx(m_yaw);
    //viewMatrix = viewMatrix * RotateXmtx(m_pitch);

    return viewMatrix;
}

void Ark::Camera::Translate(float x, float y, float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;
}

void Ark::Camera::Rotate(float pitch, float yaw)
{	
	m_yaw += yaw;

    if (pitch > 90.0f) {
        m_pitch = 90.0f;
    }
    else if (pitch < -90.0f) {
        m_pitch = -90.0f;
    }
    else {
        m_pitch += pitch;
    }
}
