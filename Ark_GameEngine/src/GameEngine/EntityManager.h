#pragma once
#include <vector>
#include <bitset>
#include <Windows.h>
#include <string>

namespace Ark {

	using Entity = unsigned int;

	class EntityManager
	{
	public:
		//Constant to allow other types to be established at compile time.
		static const unsigned int MAX_ENTITIES = 100;
		static const unsigned int MAX_COMPONENTS = 32;//Must be less than UINT_MAX
		
		//Constructor
		EntityManager();
		//Create a entity.
		Entity NewEntity();

		//Update an entity's mask.
		bool UpdateMask(Ark::Entity tgtEntity, unsigned int bitPos, bool bitState);

		//Use a system's mask to evaluate the entities that are compatible with it.
		std::vector<Ark::Entity> EvalSysEntities(std::bitset<MAX_COMPONENTS> sysFilterMask);

		//For Debugging.
		unsigned int GetEntityCount();

	private:
		//Store mask of each entity.
		std::vector<std::bitset<MAX_COMPONENTS>> m_entityMasks;

		//Entity id's that havent been assigned.
		std::vector<unsigned int> m_availableIds;

		//Count entities for debugging.
		unsigned int m_entityCount;
	};
}



