#include "Entity.h"

Ark::Entity Ark::Entity::m_activeEntities[];
std::vector<unsigned int> Ark::Entity::m_availableIds;

void Ark::Entity::Init()
{
	for (int i = 0; i < MAX_ENTITIES; i++) {
		m_availableIds.push_back(i);
	}
}
