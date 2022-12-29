#include "ComponentManager.h"

Ark::ComponentManager::ComponentManager()
{
	for (unsigned int i = EntityController::MAX_COMPONENTS - 1; m_availableIds.size() < EntityController::MAX_COMPONENTS; i--) {
		m_availableIds.push_back(i);
	}
}

int Ark::ComponentManager::GetRegisterCount()
{
	int componentSum = 0;

	for (int c = 0; c < m_componentData.size(); c++) {
		if (m_componentData[c].size() > 0) {
			componentSum += 1;
		}
	}

	return componentSum;
}

bool Ark::ComponentManager::AddComponent(Ark::Entity tgtEntity, Ark::Component newComponent)
{


	return false;
}
