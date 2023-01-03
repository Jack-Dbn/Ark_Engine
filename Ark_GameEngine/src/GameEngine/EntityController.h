#pragma once
#include <vector>
#include <bitset>
#include <Windows.h>
#include <string>

namespace Ark {

	using Entity = unsigned int;

	class EntityController
	{
	public:
		static const unsigned int MAX_ENTITIES = 100;
		static const unsigned int MAX_COMPONENTS = 32;//Must be less than UINT_MAX

		EntityController();
		Entity NewEntity();

		unsigned int GetEntityCount();

	private:
		std::bitset<MAX_COMPONENTS> m_entityMasks[MAX_ENTITIES];
		std::vector<unsigned int> m_availableIds;

		unsigned int m_entityCount;
	};
}



