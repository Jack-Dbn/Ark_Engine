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
	bool Add(unsigned int entity, T newComponent);

	bool Get(unsigned int entity, T& tgtComponent);

private:
	bool EntityExists(unsigned int entity);

	std::vector<T> m_componentData;

	std::unordered_map<unsigned int, unsigned int> m_entityMap;
};

template<typename T>
inline bool ComponentList<T>::Add(unsigned int entity, T newComponent)
{
	if (EntityExists(entity)) {
		return false;
	}

	m_entityMap[entity] = m_componentData.size();
	m_componentData.push_back(newComponent);

	return true;
}

template<typename T>
inline bool ComponentList<T>::Get(unsigned int entity, T &tgtComponent)
{
	if (!EntityExists(entity)) {
		return false;
	}

	unsigned int id = m_entityMap[entity];
	tgtComponent = m_componentData[id];

	return true;
}

template<typename T>
inline bool ComponentList<T>::EntityExists(unsigned int entity)
{
	if (m_entityMap.count(entity) == 0) {
		return false;
	}

	return true;
}
