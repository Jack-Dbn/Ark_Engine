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
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };    

    viewMatrix = viewMatrix * Ark::matrix4x4::RotateXmtx(m_pitch);
    viewMatrix = viewMatrix * Ark::matrix4x4::RotateYmtx(m_yaw);   
    
    //Calculate new position using the delta position and the cameras rotation.
    m_position.x += (viewMatrix[2][0] * m_deltaPosition.z);
    m_position.x += (viewMatrix[1][0] * m_deltaPosition.y);
    m_position.x += (viewMatrix[0][0] * m_deltaPosition.x);

    m_position.y += (viewMatrix[2][1] * m_deltaPosition.z);
    m_position.y += (viewMatrix[1][1] * m_deltaPosition.y);
    m_position.y += (viewMatrix[0][1] * m_deltaPosition.x);

    m_position.z += (viewMatrix[2][2] * m_deltaPosition.z);
    m_position.z += (viewMatrix[1][2] * m_deltaPosition.y);
    m_position.z += (viewMatrix[0][2] * m_deltaPosition.x);


    viewMatrix = viewMatrix * Ark::matrix4x4::TranslateMtx(m_position.x, m_position.y, m_position.z);

    //Reset deltas
    m_deltaPosition.x = 0;
    m_deltaPosition.y = 0;
    m_deltaPosition.z = 0;
    
    return viewMatrix;
}

void Ark::Camera::Translate(float x, float y, float z)
{
    m_deltaPosition.x += x;
    m_deltaPosition.y += y;
    m_deltaPosition.z += z;
}

void Ark::Camera::Rotate(float pitch, float yaw)
{	
	m_yaw += yaw;
    m_pitch += pitch;

    //Clamp pitch
    if (m_pitch > 90.0f) {
        m_pitch = 90.0f;
    }
    else if (m_pitch < -90.0f) {
        m_pitch = -90.0f;
    }
}
