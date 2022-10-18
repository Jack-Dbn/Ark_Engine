#include "Entity.h"

std::bitset<Ark::Entity::MAX_COMPONENTS> Ark::Entity::m_activeEntities[];
std::vector<int> Ark::Entity::m_availableIds;

void Ark::Entity::Init()
{
	for (int i = MAX_ENTITIES-1; i > -1; i--) {
		m_availableIds.push_back(i);
	}
}

Ark::Entity::Entity()
{
	m_id = -1;
}

bool Ark::Entity::Load()
{
	m_id = m_availableIds.back();
	m_availableIds.pop_back();

	if (m_id < 0) {
		return false;
	}

	return true;
}

bool Ark::Entity::Unload()
{	
	std::bitset<Ark::Entity::MAX_COMPONENTS> emptyMask;
	m_activeEntities[m_id] = emptyMask;
	m_availableIds.push_back(m_id);
	m_id = -1;

	return true;
}
