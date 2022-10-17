#pragma once
#include <vector>
#include <bitset>
#include <Windows.h>
#include <string>

namespace Ark {

	class Entity
	{
	public:
		static const unsigned int MAX_ENTITIES = 100;
		static const unsigned int MAX_COMPONENTS = 32;

		static void Init();

		//bool Load();
		//bool Unload();

	private:

		static Entity m_activeEntities[MAX_ENTITIES];
		static std::vector<unsigned int> m_availableIds;

		//unsigned int m_engineLabel[8];

		std::bitset<MAX_COMPONENTS> m_componentMask;
	};
}



