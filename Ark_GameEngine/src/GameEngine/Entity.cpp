#include "Entity.h"

std::bitset<Ark::Entity::MAX_COMPONENTS> Ark::Entity::m_activeEntities[];
std::vector<int> Ark::Entity::m_availableIds;

void Ark::Entity::Init()
{
	for (int i = MAX_ENTITIES - 1; i > -1; i--) {
		m_availableIds.push_back(i);
	}
}

void Ark::Entity::UnloadAll()
{
	std::bitset<MAX_COMPONENTS> blankMask;

	for (int i = 0; i < MAX_ENTITIES; i++) {

		if (m_activeEntities[i] == blankMask) {
			continue;
		}

		m_activeEntities[i] = blankMask;
		m_availableIds.push_back(i);
	}
}

Ark::Entity Ark::Entity::CreateEntity()
{
	Entity newEntity;
	newEntity.Load();	

	return newEntity;
}

Ark::Entity::Entity()
{
	m_id = -1;
}

int Ark::Entity::GetID()
{
	return m_id;
}

void Ark::Entity::AddComponent(Component& tgtComponent)
{
	int maskPos = tgtComponent.GetMaskPos();
	if (maskPos < 0 || maskPos >= MAX_COMPONENTS) {
		return;
	}

	m_activeEntities[m_id].set(maskPos, true);
	tgtComponent.LoadData(this->m_id);
}

bool Ark::Entity::Load()
{
	if (m_id >= 0 && m_id < MAX_ENTITIES) {
		return true;
	}

	m_id = m_availableIds.back();
	m_availableIds.pop_back();

	if (m_id < 0) {
		return false;
	}

	m_activeEntities[m_id] = m_componentMask;

	return true;
}

bool Ark::Entity::Unload()
{
	if (m_id < 0 || m_id >= MAX_ENTITIES) {
		m_id = -1;
		return true;
	}

	std::bitset<Ark::Entity::MAX_COMPONENTS> emptyMask;
	m_activeEntities[m_id] = emptyMask;
	m_availableIds.push_back(m_id);
	m_id = -1;

	return true;
}

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
