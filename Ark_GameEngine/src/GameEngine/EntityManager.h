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
		static const unsigned int MAX_ENTITIES = 100;
		static const unsigned int MAX_COMPONENTS = 32;//Must be less than UINT_MAX

		EntityManager();
		Entity NewEntity();

		bool UpdateMask(Ark::Entity tgtEntity, unsigned int bitPos, bool bitState);
		std::vector<Ark::Entity> EvalSysEntities(std::bitset<MAX_COMPONENTS> sysFilterMask);

		unsigned int GetEntityCount();

	private:
		std::vector<std::bitset<MAX_COMPONENTS>> m_entityMasks;
		std::vector<unsigned int> m_availableIds;

		unsigned int m_entityCount;
	};
}



