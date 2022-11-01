#include "Transform.h"

Ark::Transform Ark::Transform::m_activeTransforms[];

void Ark::Transform::PrintPos(int entityId)
{
	if (entityId >= 100 || entityId < 0) {
		return;
	}
	wchar_t text[256];

	swprintf_s(text, L"%d", m_activeTransforms[entityId].m_posX);
	MessageBox(NULL, text, text, 0);
}

Ark::Transform::Transform() : Component()
{
	m_posX = 0;
	m_posY = 0;
	m_posZ = 0;
}

int Ark::Transform::GetMaskPos()
{
	return maskPos;
}

void Ark::Transform::LoadData(unsigned int entityPos)
{
	m_activeTransforms[entityPos] = *this;
}

void Ark::Transform::UnloadData(unsigned int entityPos)
{
	Transform blankTransform;
	m_activeTransforms[entityPos] = blankTransform;
}

void Ark::Transform::ChangePos(int x, int y, int z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}
