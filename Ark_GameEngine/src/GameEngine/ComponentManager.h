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

		std::unordered_map<std::string, unsigned int>* GetRegister();

		template <typename T>
		bool SetComponent(Ark::Entity tgtEntity, T newComponent);

		template <typename T>
		bool GetComponent(Ark::Entity tgtEntity, T &newComponent);

		template <typename T>
		bool RemoveComponent(Ark::Entity tgtEntity);

	private:
		template <typename T>
		unsigned int GetBitPos();

		std::vector<unsigned int> m_availableIds;

		std::unordered_map<std::string, unsigned int> m_componentMap;
	
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

		m_componentMap[typeid(T).name()] = pos;

		m_componentData[pos] = std::make_shared<ComponentList<T>>();

		m_availableIds.pop_back();

		return true;
	}

	template<typename T>
	inline unsigned int ComponentManager::GetBitPos()
	{
		std::string typeNameStr = typeid(T).name();

		if (m_componentMap.find(typeNameStr) == m_componentMap.end()) {
			return UINT_MAX;//Type is not registered yet.
		}

		unsigned int bitPos = m_componentMap[typeNameStr];
				
		return bitPos;
	}

	template<typename T>
	inline bool ComponentManager::SetComponent(Ark::Entity tgtEntity, T newComponent)
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

	template<typename T>
	inline bool ComponentManager::RemoveComponent(Ark::Entity tgtEntity)
	{
		unsigned int componentID = this->GetBitPos<T>();

		std::shared_ptr<ComponentList<T>> listPtr = std::static_pointer_cast<ComponentList<T>>(m_componentData[componentID]);
		listPtr->Remove(tgtEntity);

		return true;
	}

}


