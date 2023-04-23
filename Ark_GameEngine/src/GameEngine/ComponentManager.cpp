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

bool Ark::ComponentManager::SaveTransforms()
{
	//Check if component type is already registered.
	if (this->GetBitPos<Ark::Transform>() == UINT_MAX) {
		return false;
	}

	unsigned int transformId = this->GetBitPos<Ark::Transform>();

	std::shared_ptr<ComponentList<Ark::Transform>> listPtr = std::static_pointer_cast<ComponentList<Ark::Transform>>(m_componentListData[transformId]);
	m_transformSave = *listPtr;
}

bool Ark::ComponentManager::LoadTransforms()
{
	//Check if component type is already registered.
	if (this->GetBitPos<Ark::Transform>() == UINT_MAX) {
		return false;
	}

	unsigned int transformId = this->GetBitPos<Ark::Transform>();

	std::shared_ptr<ComponentList<Ark::Transform>> listPtr = std::static_pointer_cast<ComponentList<Ark::Transform>>(m_componentListData[transformId]);
	
	//Revert transform list to save.
	*listPtr = m_transformSave;
}
