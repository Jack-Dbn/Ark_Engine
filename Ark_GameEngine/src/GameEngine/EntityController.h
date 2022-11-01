#pragma once
#include <vector>
#include <bitset>
#include <Windows.h>
#include <string>
#include "Component.h"

namespace Ark {

	using Entity = unsigned int;

	class EntityController
	{
	public:
		static const unsigned int MAX_ENTITIES = 100;
		static const int MAX_COMPONENTS = 32;

		EntityController();
		Entity NewEntity();

		void AddComponent(Entity tgtEntity, Component& newComponent);

	private:
		std::bitset<MAX_COMPONENTS> m_entityMasks[MAX_ENTITIES];
		std::vector<unsigned int> m_availableIds;
	};
}



