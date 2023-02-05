#pragma once
#include <unordered_map>

class IComponentList 
{
public:
	virtual ~IComponentList() = default;

	//virtual unsigned int GetSize() = 0;
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
	if (!EntityExists(entity)) {
		return false;
	}	
	
	if (m_componentData.size() > 1) {

		unsigned int id = m_entityMap[entity];

		unsigned int swapId = m_componentData.size() - 1;
		Ark::Entity swapEntity = m_idMap[swapId];//Find entity id of back element.

		m_componentData[id] = m_componentData.back();//Data of compontent to be removed is set to back element
		m_componentData.pop_back();

		m_entityMap[swapEntity] = id;//Former back entity now says id is old deleted components id.
		m_entityMap.erase(entity);//Delete component from entity map.

		m_idMap[id] = swapEntity;
		m_idMap.erase(swapId);		
		
	}
	else {
		m_componentData.clear();
		m_entityMap.clear();
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
