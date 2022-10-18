#pragma once
#include <vector>
#include <bitset>
#include <Windows.h>
#include <string>

namespace Ark {

	class Entity
	{
	public:
		static const int MAX_ENTITIES = 100;
		static const int MAX_COMPONENTS = 32;

		static void Init();

		Entity();

		bool Load();
		bool Unload();

		int m_id;

		std::bitset<MAX_COMPONENTS> m_componentMask;

	private:

		static std::bitset<MAX_COMPONENTS> m_activeEntities[MAX_ENTITIES];
		static std::vector<int> m_availableIds;

		
	};
}



