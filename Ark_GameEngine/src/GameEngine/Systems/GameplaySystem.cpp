#include "GameplaySystem.h"

Ark::GameplaySystem::GameplaySystem()
{
}

int Ark::GameplaySystem::Initialise(bool* isGameRunning)
{
    m_gameActive = isGameRunning;

    return 0;
}

int Ark::GameplaySystem::Update(Ark::ComponentManager& engineCM)
{
    if (!m_gameActive) {
        return 0;
    }

    std::vector<Ark::Entity> playerEntities;
    std::vector<Ark::Entity> triggerEntities;

    for (int i = 0; i < m_EntityList.size(); i++) {
        //Note entity id.
        Ark::Entity entityId = m_EntityList[i];

        Ark::Logic logic;
        engineCM.GetComponent<Ark::Logic>(entityId, logic);

        Ark::Transform transform;
        engineCM.GetComponent<Ark::Transform>(entityId, transform);

        if (logic.GetType() == Ark::Player) {
            playerEntities.push_back(entityId);
        }
        else {
            triggerEntities.push_back(entityId);
        }
    }

    for (int p = 0; p < playerEntities.size(); p++) {
        for (int e = 0; e < triggerEntities.size(); e++) {

            //Get entity id for player and trigger
            Ark::Entity playerEntity = playerEntities[p];
            Ark::Entity triggerEntity = triggerEntities[e];

            //Get logic components for player and trigger
            Ark::Logic playerLogic;
            Ark::Logic triggerLogic;
            engineCM.GetComponent<Ark::Logic>(playerEntity, playerLogic);
            engineCM.GetComponent<Ark::Logic>(triggerEntity, triggerLogic);

            //Get transform components for player and trigger
            Ark::Transform playerTransform;
            Ark::Transform triggerTransform;
            engineCM.GetComponent<Ark::Transform>(playerEntity, playerTransform);
            engineCM.GetComponent<Ark::Transform>(triggerEntity, triggerTransform);

            
            Ark::vector3D playerPos = playerTransform.GetPos();
            Ark::vector3D tiggerPos = triggerTransform.GetPos();

            Ark::vector3D deltaPos(tiggerPos.x - playerPos.x, tiggerPos.y - playerPos.y, tiggerPos.z - playerPos.z);

            float distance = sqrt(pow(deltaPos.x, 2) + pow(deltaPos.y, 2) + pow(deltaPos.z, 2));
            
            //Check if collision has occured between player and trigger.
            if (distance < (playerLogic.GetRadius() + triggerLogic.GetRadius())) {
                this->Collision(engineCM, triggerLogic.GetType());
                return 0;
            }            
        }
    }

    return 0;
}

bool Ark::GameplaySystem::Collision(Ark::ComponentManager& engineCM, Ark::ObjectType triggerType)
{
    if (triggerType == Ark::Goal) {
        engineCM.LoadTransforms();

        *m_gameActive = false;
        MessageBox(NULL, L"Game Over - Success!", L"Game Over - Success!", 0);
    }
    else {
        engineCM.LoadTransforms();

        *m_gameActive = false;
        MessageBox(NULL, L"Game Over - Fail", L"Game Over - Fail", 0);
    }

    return true;
}

int Ark::GameplaySystem::Release()
{
    return 0;
}

