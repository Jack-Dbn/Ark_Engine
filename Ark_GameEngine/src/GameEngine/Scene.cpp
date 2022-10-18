#include "Scene.h"

void Ark::Scene::AddEntity(Entity newEntity)
{
	m_entityList.push_back(newEntity);
}

std::vector<Ark::Entity> Ark::Scene::GetEntityList()
{
	return m_entityList;
}
