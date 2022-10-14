#pragma once
#include <vector>
#include <bitset>
#include <Windows.h>

const unsigned int MAX_COMPONENTS = 32;

namespace Ark {
	class Entity
	{
	public:
		Entity();
		~Entity();

		static void Initialise(unsigned int maxEntities);
		
		void Load();

		void Unload();

	private:
		int m_id;

		std::bitset<MAX_COMPONENTS> m_componentMask;
	};

	static std::vector<unsigned int> freeEntitySlots;

	static std::vector<Entity> activeEntities;

}



