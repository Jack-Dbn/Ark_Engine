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
	Translate(x,y,z);

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_scaleZ = 1.0f;

	UpdateTransformMtx();
}

void Ark::Transform::Translate(float x, float y, float z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;

	UpdateTransformMtx();
}

void Ark::Transform::Rotate(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;

	UpdateTransformMtx();
}

void Ark::Transform::Scale(float x, float y, float z)
{
	m_scaleX = x;
	m_scaleY = y;
	m_scaleZ = z;

	UpdateTransformMtx();
}

Ark::matrix4x4 Ark::Transform::GetModelMtx()
{	
	return m_transformMtx;
}

bool Ark::Transform::UpdateTransformMtx()
{
	Ark::matrix4x4 modelMtx('i');

	Ark::matrix4x4 translateMtx = {
		1.0f, 0.0f, 0.0f, m_posX,
		0.0f, 1.0f, 0.0f, m_posY,
		0.0f, 0.0f, 1.0f, m_posZ,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	Ark::matrix4x4 rotateMtx('i');
	
	Ark::matrix4x4 rotateTemp('i');
	rotateTemp = rotateTemp.RotateZmtx(m_rotationZ);
	rotateMtx = rotateMtx * rotateTemp;

	rotateTemp = rotateTemp.RotateXmtx(m_rotationX);
	rotateMtx = rotateMtx * rotateTemp;

	rotateTemp = rotateTemp.RotateYmtx(m_rotationY);
	rotateMtx = rotateMtx * rotateTemp;

	Ark::matrix4x4 scaleMtx = {
		m_scaleX, 0.0f, 0.0f, 0.0f,
		0.0f, m_scaleY, 0.0f, 0.0f,
		0.0f, 0.0f, m_scaleZ, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	
	modelMtx = modelMtx * translateMtx;	
	modelMtx = modelMtx * rotateMtx;
	modelMtx = modelMtx * scaleMtx;
	
	

	m_transformMtx = modelMtx;

	return true;
}
