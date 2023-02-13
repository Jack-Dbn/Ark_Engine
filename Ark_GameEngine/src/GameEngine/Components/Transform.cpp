#include "Transform.h"

Ark::Transform::Transform() : Component()
{
	m_posX = 0;
	m_posY = 0;
	m_posZ = 0;
}

void Ark::Transform::ChangePos(float x, float y, float z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}

Ark::matrix4x4 Ark::Transform::GetModelMtx()
{
	Ark::matrix4x4 modelMtx;
	modelMtx.SetIdentity();

	Ark::matrix4x4 translateMtx = Ark::matrix4x4();
	Ark::matrix4x4 rotateMtx = Ark::matrix4x4();
	Ark::matrix4x4 scaleMtx = Ark::matrix4x4();

	return modelMtx;
}
