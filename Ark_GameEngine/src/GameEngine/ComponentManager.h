#pragma once
#include <typeinfo>
#include <memory>
#include "EntityManager.h"
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
		unsigned int GetBitPos();

		template <typename T>
		bool SetComponent(Ark::Entity tgtEntity, T newComponent);

		template <typename T>
		bool GetComponent(Ark::Entity tgtEntity, T &newComponent);

		template <typename T>
		bool RemoveComponent(Ark::Entity tgtEntity);

	private:	

		std::vector<unsigned int> m_availableIds;

		std::unordered_map<std::string, unsigned int> m_componentMap;
	
		std::vector<std::shared_ptr<IComponentList>> m_componentListData = std::vector<std::shared_ptr<IComponentList>>(EntityManager::MAX_COMPONENTS);
	};

	template<typename T>
	inline bool ComponentManager::RegisterComponent()
	{
		unsigned int pos = m_availableIds.back();

		if (pos >= EntityManager::MAX_COMPONENTS) {
			return false;
		}

		if (this->GetBitPos<T>() != UINT_MAX) {
			return false;//Already registered
		}

		m_componentMap[typeid(T).name()] = pos;

		m_componentListData[pos] = std::make_shared<ComponentList<T>>();

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
		std::shared_ptr<ComponentList<T>> listPtr = std::static_pointer_cast<ComponentList<T>>(m_componentListData[componentID]);
		listPtr->Set(tgtEntity, newComponent);

		return true;
	}

	template<typename T>
	inline bool ComponentManager::GetComponent(Ark::Entity tgtEntity, T &tgtComponent)
	{
		unsigned int componentID = this->GetBitPos<T>();

		std::shared_ptr<ComponentList<T>> listPtr = std::static_pointer_cast<ComponentList<T>>(m_componentListData[componentID]);
		listPtr->Get(tgtEntity, tgtComponent);

		return true;
	}

	template<typename T>
	inline bool ComponentManager::RemoveComponent(Ark::Entity tgtEntity)
	{
		unsigned int componentID = this->GetBitPos<T>();

		std::shared_ptr<ComponentList<T>> listPtr = std::static_pointer_cast<ComponentList<T>>(m_componentListData[componentID]);
		listPtr->Remove(tgtEntity);

		return true;
	}

}


