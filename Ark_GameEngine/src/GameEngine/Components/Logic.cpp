#include "Logic.h"

Ark::Logic::Logic()
{
	m_collisionRadius = 0.0f;
	m_type = Ark::Hazard;
}

Ark::Logic::Logic(ObjectType type, float collisionRadius)
{
	m_collisionRadius = collisionRadius;
	m_type = type;
}

void Ark::Logic::SetType(ObjectType newType)
{
	m_type = newType;
}

Ark::ObjectType Ark::Logic::GetType()
{
	return m_type;
}

void Ark::Logic::SetRadius(float newRadius)
{
	m_collisionRadius = newRadius;
}

float Ark::Logic::GetRadius()
{
	return m_collisionRadius;
}
