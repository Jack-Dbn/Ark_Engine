#pragma once
#include <vector>
#include <bitset>
#include <Windows.h>
#include <string>
#include "Component.h"

namespace Ark {

	class Entity
	{
	public:
		static const int MAX_ENTITIES = 100;
		static const int MAX_COMPONENTS = 32;

		static void Init();
		static void UnloadAll();

		static Entity CreateEntity();

		Entity();

		int GetID();

		void AddComponent(Component& tgtComponent);

		bool Load();
		bool Unload();

		//Debug
		static void PrintActive(int numElements);

	private:
		static std::bitset<MAX_COMPONENTS> m_activeEntities[MAX_ENTITIES];
		static std::vector<int> m_availableIds;

		int m_id;

		std::bitset<MAX_COMPONENTS> m_componentMask;
	};
}



