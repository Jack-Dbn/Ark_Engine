#include "EntityController.h"

Ark::EntityController::EntityController()
{
	for(unsigned int i = MAX_ENTITIES-1; m_availableIds.size() < MAX_ENTITIES; i--) {
		m_availableIds.push_back(i);
	}

	m_entityMasks.reserve(MAX_ENTITIES);
	m_entityCount = 0;
}

Ark::Entity Ark::EntityController::NewEntity()
{
	if (m_availableIds.size() <= 0) {
		MessageBox(NULL, L"Max Entities Reached", L"Max Entities Reached", 0);
		return UINT_MAX;
	}

	Entity newEntity = m_availableIds.back();
	m_availableIds.pop_back();

	std::bitset<MAX_COMPONENTS> newMask;
	if (m_entityMasks.size() < newEntity+1) {
		m_entityMasks.resize(newEntity+1);
	}
	m_entityMasks[newEntity] = newMask;

	m_entityCount++;

	return newEntity;
}

bool Ark::EntityController::UpdateMask(Ark::Entity tgtEntity, unsigned int bitPos, bool bitState)
{
	if (tgtEntity > m_entityMasks.size() || bitPos >= MAX_COMPONENTS) {
		return false;
	}

	m_entityMasks[tgtEntity][bitPos] = bitState;

	return true;
}

std::vector<Ark::Entity> Ark::EntityController::EvalSysEntities(std::bitset<MAX_COMPONENTS> sysFilterMask)
{
	std::vector<Ark::Entity> systemEntities;

	for (Ark::Entity i = 0; i < m_entityMasks.size(); i++) {
		if ((m_entityMasks[i] & sysFilterMask) == sysFilterMask) {
			systemEntities.push_back(i);
		}
	}

	return systemEntities;
}

unsigned int Ark::EntityController::GetEntityCount()
{
	return m_entityCount;
}
