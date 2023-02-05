#pragma once
#include "ComponentManager.h"
#include "Components/Transform.h"
#include "Components/Model.h"
#include "Components/Material.h"

class System
{
public:
	virtual int Initialise() = 0;
	virtual int Update(Ark::ComponentManager& engineCM) = 0;
	virtual int Release() = 0;

	template <typename T>
	bool AddReqComponent(std::unordered_map<std::string, unsigned int>* registeredTypes);

	std::bitset<Ark::EntityController::MAX_COMPONENTS> GetFilterMask();
	bool SetEntityList(std::vector<unsigned int> newEntityList);

protected:
	std::vector<unsigned int> m_EntityList;

	std::bitset<Ark::EntityController::MAX_COMPONENTS> m_filterMask;
};

template<typename T>
inline bool System::AddReqComponent(std::unordered_map<std::string, unsigned int>* registeredTypes)
{
	std::string typeName = typeid(T).name();

	if ((*registeredTypes).find(typeName) == (*registeredTypes).end()) {
		return false;
	}

	unsigned int bitPos = (*registeredTypes)[typeName];
	m_filterMask[bitPos] = 1;

	return true;
}
