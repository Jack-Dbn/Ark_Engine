#include "EntityManager.h"

//Constructor 
Ark::EntityManager::EntityManager()
{
	//At start all values between 0 and MAX_ENTITIES are available.
	for(unsigned int i = MAX_ENTITIES-1; m_availableIds.size() < MAX_ENTITIES; i--) {
		m_availableIds.push_back(i);
	}

	//Reserve space needed in memory.
	m_entityMasks.reserve(MAX_ENTITIES);
	m_entityCount = 0;
}

//Create a entity.
Ark::Entity Ark::EntityManager::NewEntity()
{
	//Check to ensure at least one id is free to be assigned.
	if (m_availableIds.size() <= 0) {
		MessageBox(NULL, L"Max Entities Reached", L"Max Entities Reached", 0);
		return UINT_MAX;
	}

	//Assign entity id as back element.
	Entity newEntity = m_availableIds.back();
	m_availableIds.pop_back();//Remove back element.

	//Create entity's component mask.
	std::bitset<MAX_COMPONENTS> newMask;
	if (m_entityMasks.size() < newEntity+1) {
		m_entityMasks.resize(newEntity+1);
	}
	m_entityMasks[newEntity] = newMask;

	//Increase entity count.
	m_entityCount++;
	
	//Return new entity id.
	return newEntity;
}

bool Ark::EntityManager::UpdateMask(Ark::Entity tgtEntity, unsigned int bitPos, bool bitState)
{
	//Check value provided isnt out of range.
	if (tgtEntity > m_entityMasks.size() || bitPos >= MAX_COMPONENTS) {
		return false;//Indicate failure.
	}

	//Set value.
	m_entityMasks[tgtEntity][bitPos] = bitState;

	return true;
}

std::vector<Ark::Entity> Ark::EntityManager::EvalSysEntities(std::bitset<MAX_COMPONENTS> sysFilterMask)
{
	std::vector<Ark::Entity> systemEntities;

	//Check for each entity...
	for (Ark::Entity i = 0; i < m_entityMasks.size(); i++) {
		if ((m_entityMasks[i] & sysFilterMask) == sysFilterMask) {//Perform bitwise and operation between entity and system mask.
			systemEntities.push_back(i);//Add compatible entity to vector.
		}
	}

	return systemEntities;
}

unsigned int Ark::EntityManager::GetEntityCount()
{
	return m_entityCount;
}
