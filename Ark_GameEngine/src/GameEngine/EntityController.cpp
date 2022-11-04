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
}

Ark::Entity Ark::EntityController::NewEntity()
{
	if (m_availableIds.size() <= 0) {
		MessageBox(NULL, L"Max Entities Reached", L"Max Entities Reached", 0);
	}

	Entity newEntity = m_availableIds.back();
	m_availableIds.pop_back();

	return newEntity;
}
