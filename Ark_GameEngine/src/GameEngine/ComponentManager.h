#pragma once
#include <typeinfo>
#include "EntityController.h"
#include "Component.h"

namespace Ark {
	class ComponentManager
	{
	public:
		ComponentManager();

		template <typename T>
		bool RegisterComponent();

		template <typename T>
		unsigned int GetComponentID();

		int GetRegisterCount();

		bool AddComponent(Ark::Entity tgtEntity, Ark::Component newComponent);

	private:
		std::vector<unsigned int> m_availableIds;

		std::string m_componentTypes[EntityController::MAX_COMPONENTS];
	
		std::vector<std::vector<Component>> m_componentData = std::vector<std::vector<Component>>(EntityController::MAX_COMPONENTS);
	};

	template<typename T>
	inline bool ComponentManager::RegisterComponent()
	{
		unsigned int pos = m_availableIds.back();

		if (pos >= EntityController::MAX_COMPONENTS) {
			return false;
		}

		m_availableIds.pop_back();

		m_componentTypes[pos] = typeid(T).name();

		std::vector<Component> entityData(EntityController::MAX_ENTITIES);
		m_componentData[pos] = entityData;

		return true;
	}

	template<typename T>
	inline unsigned int ComponentManager::GetComponentID()
	{
		for (int i = 0; i < EntityController::MAX_COMPONENTS; i++) {
			
			std::string typeNameStr = typeid(T).name();

			if (m_componentTypes[i] == typeNameStr) {
				return i;
			}
		}

		//Type is not registered yet.
		return UINT_MAX;
	}	
}


