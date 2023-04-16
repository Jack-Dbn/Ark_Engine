#pragma once
#include <unordered_map>

class IComponentList 
{
public:
	virtual ~IComponentList() = default;
};

template<typename T>
class ComponentList : public IComponentList
{
public:
	bool Add(Ark::Entity entity, T newComponent);

	bool Set(Ark::Entity entity, T newComponent);

	bool Get(Ark::Entity entity, T& tgtComponent);

	bool Remove(Ark::Entity entity);

private:
	bool EntityExists(Ark::Entity entity);

	std::vector<T> m_componentData;

	std::unordered_map<Ark::Entity, unsigned int> m_entityMap;
	std::unordered_map<unsigned int, Ark::Entity> m_idMap;
};

template<typename T>
inline bool ComponentList<T>::Add(Ark::Entity entity, T newComponent)
{
	if (EntityExists(entity)) {
		return false;
	}

	m_entityMap[entity] = m_componentData.size();
	m_idMap[m_componentData.size()] = entity;

	m_componentData.push_back(newComponent);

	return true;
}

template<typename T>
inline bool ComponentList<T>::Set(Ark::Entity entity, T newComponent)
{
	if (!EntityExists(entity)) {
		return this->Add(entity, newComponent);
	}

	unsigned int id = m_entityMap[entity];
	m_componentData[id] = newComponent;

	return true;
}

template<typename T>
inline bool ComponentList<T>::Get(Ark::Entity entity, T &tgtComponent)
{
	if (!EntityExists(entity)) {
		return false;
	}

	unsigned int id = m_entityMap[entity];
	tgtComponent = m_componentData[id];

	return true;
}

template<typename T>
inline bool ComponentList<T>::Remove(Ark::Entity entity)
{
	//If entity doesnt exist, no reason to continue
	if (!EntityExists(entity)) {
		return false;
	}	
	
	//If more than one component exists, optimisation is required
	if (m_componentData.size() > 1) {

		//Get index of component to remove.
		unsigned int id = m_entityMap[entity];

		//Get index of last component in vector.
		unsigned int swapId = m_componentData.size() - 1;
		Ark::Entity swapEntity = m_idMap[swapId];//Find entity id of last element.

		//Component getting deleted is overwritten with back element.
		m_componentData[id] = m_componentData.back();
		//Back element is removed.
		m_componentData.pop_back();

		//Former back element is set to new position.
		m_entityMap[swapEntity] = id;
		m_entityMap.erase(entity);//Delete removed component from entity map.

		//Old entity position is set to old back entity.
		m_idMap[id] = swapEntity;
		m_idMap.erase(swapId);//Remove index of last element.	
		
	}
	else {
		//Only component left can be removed by clearing data structures.
		m_componentData.clear();
		m_entityMap.clear();
		m_idMap.clear();
	}

	return true;
}

template<typename T>
inline bool ComponentList<T>::EntityExists(Ark::Entity entity)
{
	if (m_entityMap.count(entity) == 0) {
		return false;
	}

	return true;
}
