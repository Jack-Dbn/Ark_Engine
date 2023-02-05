#include "EntityController.h"

/*
void Ark::Entity::PrintActive(int numElements)
{
	if (numElements >= MAX_ENTITIES || numElements < 0) {
		return;
	}

	std::bitset<Ark::Entity::MAX_COMPONENTS> emptyMask;
	wchar_t text[256];

	for (int e = 0; e < numElements; e++) {
		swprintf_s(text, L"%d", m_activeEntities[e]);
		MessageBox(NULL, text, text, 0);
	}
}
*/

Ark::EntityController::EntityController()
{
	for(unsigned int i = MAX_ENTITIES-1; m_availableIds.size() < MAX_ENTITIES; i--) {
		m_availableIds.push_back(i);
	}

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
	m_entityMasks.push_back(newMask);

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
