#pragma once
#include <vector>
#include <bitset>
#include <Windows.h>

const unsigned int MAX_COMPONENTS = 32;

static std::vector<unsigned int> freeEntitySlots;

namespace Ark {
	class Entity
	{
	public:
		Entity();
		~Entity();

		static void Initialise(unsigned int maxEntities);

	private:
		unsigned int m_id;

		std::bitset<MAX_COMPONENTS> m_componentMask;
	};

}

