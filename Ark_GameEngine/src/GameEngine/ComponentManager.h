#pragma once
#include <typeinfo>
#include <memory>
#include "EntityManager.h"
#include "ComponentList.h"
#include "Components/Transform.h"

namespace Ark {
	class ComponentManager
	{
	public:
		ComponentManager();

		//Allow component type to be used in the engine.
		template <typename T>
		bool RegisterComponent();		

		//Debugging - ensures component types are being registered.
		int GetRegisterCount();

		//Based on type specfied, get position of component list in m_componentListData
		std::unordered_map<std::string, unsigned int>* GetRegister();
		template <typename T>
		unsigned int GetBitPos();

		//CRUD methods - for modifying component data.
		template <typename T>
		bool SetComponent(Ark::Entity tgtEntity, T newComponent);

		template <typename T>
		bool GetComponent(Ark::Entity tgtEntity, T &newComponent);

		template <typename T>
		bool RemoveComponent(Ark::Entity tgtEntity);

		//Ensure creating and loading the back of the transforms.
		bool SaveTransforms();
		bool LoadTransforms();

	private:	
		//Bit pos' that can be assigned to a new component type.
		std::vector<unsigned int> m_availableIds;

		//Map type name string to bit pos.
		std::unordered_map<std::string, unsigned int> m_componentMap;
	
		//Stores the Component Data in lists for each type.
		std::vector<std::shared_ptr<IComponentList>> m_componentListData = std::vector<std::shared_ptr<IComponentList>>(EntityManager::MAX_COMPONENTS);

		//Backs up design version of transforms.
		ComponentList<Ark::Transform> m_transformSave;	
	};

	template<typename T>
	inline bool ComponentManager::RegisterComponent()
	{
		//Get an available component id.
		unsigned int pos = m_availableIds.back();

		//If id out of range invalidate register attempt.
		if (pos >= EntityManager::MAX_COMPONENTS) {
			return false;
		}

		//Check if component type is already registered.
		if (this->GetBitPos<T>() != UINT_MAX) {
			return false;
		}

		//Add type to component-index map.
		m_componentMap[typeid(T).name()] = pos;

		//Create component list.
		m_componentListData[pos] = std::make_shared<ComponentList<T>>();

		//Remove id so it cannot be reused.
		m_availableIds.pop_back();

		return true;
	}

	template<typename T>
	inline unsigned int ComponentManager::GetBitPos()
	{
		//Convert type to string.
		std::string typeNameStr = typeid(T).name();

		//Use component map to find out if type is registered.
		if (m_componentMap.find(typeNameStr) == m_componentMap.end()) {
			return UINT_MAX;//Type is not registered yet.
		}

		//Return position of component list in m_componentListData
		unsigned int bitPos = m_componentMap[typeNameStr];
				
		return bitPos;
	}

	//Assign component to the entity specified.
	template<typename T>
	inline bool ComponentManager::SetComponent(Ark::Entity tgtEntity, T newComponent)
	{
		//Get position of component list in m_componentListData
		unsigned int componentID = this->GetBitPos<T>();

		//Create pointer to list for specfied type.
		std::shared_ptr<ComponentList<T>> listPtr = std::static_pointer_cast<ComponentList<T>>(m_componentListData[componentID]);

		//Take new component and assign it to target entity.
		listPtr->Set(tgtEntity, newComponent);

		return true;
	}

	//Retrieve the component data of the entity specified.
	template<typename T>
	inline bool ComponentManager::GetComponent(Ark::Entity tgtEntity, T &tgtComponent)
	{
		//Get position of component list in m_componentListData
		unsigned int componentID = this->GetBitPos<T>();

		//Create pointer to list for specfied type.
		std::shared_ptr<ComponentList<T>> listPtr = std::static_pointer_cast<ComponentList<T>>(m_componentListData[componentID]);

		//Retrieve component data.
		listPtr->Get(tgtEntity, tgtComponent);

		return true;
	}

	template<typename T>
	inline bool ComponentManager::RemoveComponent(Ark::Entity tgtEntity)
	{
		//Get position of component list in m_componentListData
		unsigned int componentID = this->GetBitPos<T>();

		//Create pointer to list for specfied type.
		std::shared_ptr<ComponentList<T>> listPtr = std::static_pointer_cast<ComponentList<T>>(m_componentListData[componentID]);

		//Remove the component of this type from the entity.
		listPtr->Remove(tgtEntity);

		return true;
	}

}


