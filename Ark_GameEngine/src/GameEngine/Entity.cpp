#include "Entity.h"

unsigned int Entity::m_IdCounter = 0;

Entity::Entity() {
	m_Id = m_IdCounter++;
}

unsigned int Entity::GetId() {
	return m_Id;
}