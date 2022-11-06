#include "ComponentManager.h"

Ark::ComponentManager::ComponentManager()
{
	for (unsigned int i = EntityController::MAX_COMPONENTS - 1; m_availableIds.size() < EntityController::MAX_COMPONENTS; i--) {
		m_availableIds.push_back(i);
	}
}

bool Ark::ComponentManager::AddComponent(Ark::Entity tgtEntity, Ark::Component newComponent)
{
	return false;
}
