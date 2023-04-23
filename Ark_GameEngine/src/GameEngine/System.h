#pragma once
#include "ComponentManager.h"
#include "Components/Transform.h"
#include "Components/Model.h"
#include "Components/Material.h"

class System
{
public:
	virtual int Initialise(bool* isGameRunning) = 0;
	virtual int Update(Ark::ComponentManager& engineCM) = 0;
	virtual int Release() = 0;

	template <typename T>
	bool AddReqComponent(std::unordered_map<std::string, unsigned int>* registeredTypes);

	std::bitset<Ark::EntityManager::MAX_COMPONENTS> GetFilterMask();
	bool SetEntityList(std::vector<unsigned int> newEntityList);

protected:
	std::vector<unsigned int> m_EntityList;

	std::bitset<Ark::EntityManager::MAX_COMPONENTS> m_filterMask;
};

template<typename T>
inline bool System::AddReqComponent(std::unordered_map<std::string, unsigned int>* registeredTypes)
{
	//Find the string name of the type specified.
	std::string typeName = typeid(T).name();

	//Check the type is registered.
	if ((*registeredTypes).find(typeName) == (*registeredTypes).end()) {
		return false;
	}

	//Get index of component type.
	unsigned int bitPos = (*registeredTypes)[typeName];
	m_filterMask[bitPos] = 1;//Switch bit on in filter mask to show component type is required.

	return true;
}
