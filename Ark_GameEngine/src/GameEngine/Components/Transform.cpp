#include "Transform.h"

Ark::Transform::Transform() : Component()
{
	m_posX = 0.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_scaleZ = 1.0f;

	UpdateTransformMtx();
}

Ark::Transform::Transform(float x, float y, float z)
{
	SetPosition(x,y,z);

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_scaleZ = 1.0f;

	UpdateTransformMtx();
}

void Ark::Transform::SetPosition(float x, float y, float z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;

	UpdateTransformMtx();
}

void Ark::Transform::SetOrientation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;

	UpdateTransformMtx();
}

void Ark::Transform::SetScale(float x, float y, float z)
{
	m_scaleX = x;
	m_scaleY = y;
	m_scaleZ = z;

	UpdateTransformMtx();
}

void Ark::Transform::Translate(float x, float y, float z)
{
	m_posX += x;
	m_posY += y;
	m_posZ += z;

	UpdateTransformMtx();
}

void Ark::Transform::Rotate(float x, float y, float z)
{
	m_rotationX += x;
	m_rotationY += y;
	m_rotationZ += z;

	UpdateTransformMtx();
}

void Ark::Transform::Resize(float x, float y, float z)
{
	m_scaleX += x;
	m_scaleY += y;
	m_scaleZ += z;

	UpdateTransformMtx();
}

Ark::matrix4x4 Ark::Transform::GetModelMtx()
{	
	return m_transformMtx;
}

bool Ark::Transform::UpdateTransformMtx()
{
	//Create matrix that stores combination of rotations.
	Ark::matrix4x4 rotateMtx = Ark::matrix4x4::RotateZmtx(m_rotationZ);
	rotateMtx = rotateMtx * Ark::matrix4x4::RotateXmtx(m_rotationX);
	rotateMtx = rotateMtx * Ark::matrix4x4::RotateYmtx(m_rotationY);
	
	//Form model matrix through Scaling-Rotation-Translation

	//Start with scale matrix.
	Ark::matrix4x4 modelMtx = Ark::matrix4x4::ScaleMtx(m_scaleX, m_scaleY, m_scaleZ);

	//Apply rotation matrix.
	modelMtx = rotateMtx * modelMtx;

	//Apply translation matrix.
	modelMtx = Ark::matrix4x4::TranslateMtx(m_posX, m_posY, m_posZ) * modelMtx;

	//Store model matrix in transform
	m_transformMtx = modelMtx;

	return true;
}
