#include "Transform.h"

Ark::Transform::Transform() : Component()
{
	m_posX = 0;
	m_posY = 0;
	m_posZ = 0;
}

void Ark::Transform::ChangePos(int x, int y, int z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}
