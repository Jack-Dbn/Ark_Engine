#pragma once
#include <vector>
#include "Entity.h"

namespace Ark {
	class Scene
	{
	public:
		void AddEntity(Entity newEntity);

		std::vector<Ark::Entity> GetEntityList();

	private:
		std::vector<Ark::Entity> m_entityList;
	};
}


