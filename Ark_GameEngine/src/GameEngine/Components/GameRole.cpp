#include "GameRole.h"

Ark::GameRole::GameRole()
{
	m_collisionRadius = 0.0f;
	m_role = Ark::Hazard;
}

Ark::GameRole::GameRole(Role type, float collisionRadius)
{
	m_collisionRadius = collisionRadius;
	m_role = type;
}

void Ark::GameRole::SetType(Role newType)
{
	m_role = newType;
}

Ark::Role Ark::GameRole::GetType()
{
	return m_role;
}

void Ark::GameRole::SetRadius(float newRadius)
{
	m_collisionRadius = newRadius;
}

float Ark::GameRole::GetRadius()
{
	return m_collisionRadius;
}
