#pragma once
#include <typeinfo>
#include <memory>
#include "EntityController.h"
#include "Component.h"
#include "ComponentList.h"

namespace Ark {
	class ComponentManager
	{
	public:
		ComponentManager();

		template <typename T>
		bool RegisterComponent();		

		int GetRegisterCount();

		template <typename T>
		bool AddComponent(Ark::Entity tgtEntity, T newComponent);

		template <typename T>
		bool GetComponent(Ark::Entity tgtEntity, T &newComponent);

	private:
		template <typename T>
		unsigned int GetBitPos();

		std::vector<unsigned int> m_availableIds;

		std::string m_componentTypes[EntityController::MAX_COMPONENTS];
	
		std::vector<std::shared_ptr<IComponentList>> m_componentData = std::vector<std::shared_ptr<IComponentList>>(EntityController::MAX_COMPONENTS);
	};

	template<typename T>
	inline bool ComponentManager::RegisterComponent()
	{
		unsigned int pos = m_availableIds.back();

		if (pos >= EntityController::MAX_COMPONENTS) {
			return false;
		}

		if (this->GetBitPos<T>() != UINT_MAX) {
			return false;//Already registered
		}

		m_componentTypes[pos] = typeid(T).name();

		m_componentData[pos] = std::make_shared<ComponentList<T>>();

		m_availableIds.pop_back();

		return true;
	}

	template<typename T>
	inline unsigned int ComponentManager::GetBitPos()
	{
		std::string typeNameStr = typeid(T).name();

		for (int i = 0; i < EntityController::MAX_COMPONENTS; i++) {	
			
			if (m_componentTypes[i] == typeNameStr) {
				return i;
			}
		}

		//Type is not registered yet.
		return UINT_MAX;
	}

	template<typename T>
	inline bool ComponentManager::AddComponent(Ark::Entity tgtEntity, T newComponent)
	{
		unsigned int componentID = this->GetBitPos<T>();
		std::shared_ptr<ComponentList<T>> listPtr = std::static_pointer_cast<ComponentList<T>>(m_componentData[componentID]);
		listPtr->Add(tgtEntity, newComponent);

		return true;
	}

	template<typename T>
	inline bool ComponentManager::GetComponent(Ark::Entity tgtEntity, T &tgtComponent)
	{
		unsigned int componentID = this->GetBitPos<T>();

		std::shared_ptr<ComponentList<T>> listPtr = std::static_pointer_cast<ComponentList<T>>(m_componentData[componentID]);
		listPtr->Get(tgtEntity, tgtComponent);

		return true;
	}

}


