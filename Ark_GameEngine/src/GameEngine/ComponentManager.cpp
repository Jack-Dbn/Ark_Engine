#include "ComponentManager.h"

Ark::ComponentManager::ComponentManager()
{
	for (unsigned int i = EntityManager::MAX_COMPONENTS - 1; m_availableIds.size() < EntityManager::MAX_COMPONENTS; i--) {
		m_availableIds.push_back(i);
	}
}

int Ark::ComponentManager::GetRegisterCount()
{	
	int componentSum = 0;
	
	for (int c = 0; c < m_componentListData.size(); c++) {
		if (m_componentListData[c]) {
			componentSum++;
		}
	}
	
	return componentSum;
}

std::unordered_map<std::string, unsigned int>* Ark::ComponentManager::GetRegister()
{
	return &m_componentMap;
}
