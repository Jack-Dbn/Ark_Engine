#include "GameLogicSystem.h"

Ark::GameLogicSystem::GameLogicSystem()
{
}

int Ark::GameLogicSystem::Initialise(bool* isGameRunning)
{
    m_gameActive = isGameRunning;

    return 0;
}

int Ark::GameLogicSystem::Update(Ark::ComponentManager& engineCM)
{
    //Only operate if engine is in testing phase.
    if (!m_gameActive) {
        return 0;
    }

    std::vector<Ark::Entity> playerEntities;
    std::vector<Ark::Entity> elementEntities;

    //Sort entities by role.
    for (int i = 0; i < m_EntityList.size(); i++) {
        //Note entity id.
        Ark::Entity entityId = m_EntityList[i];

        Ark::GameRole logic;
        engineCM.GetComponent<Ark::GameRole>(entityId, logic);

        Ark::Transform transform;
        engineCM.GetComponent<Ark::Transform>(entityId, transform);

        if (logic.GetRole() == Ark::Player) {
            playerEntities.push_back(entityId);
        }
        else {
            elementEntities.push_back(entityId);
        }
    }

    //Find distances between players and objectives.
    for (int p = 0; p < playerEntities.size(); p++) {
        for (int e = 0; e < elementEntities.size(); e++) {

            //Get entity id for player and trigger
            Ark::Entity playerEntity = playerEntities[p];
            Ark::Entity elementEntity = elementEntities[e];

            //Get logic components for player and trigger
            Ark::GameRole playerLogic;
            Ark::GameRole elementLogic;
            engineCM.GetComponent<Ark::GameRole>(playerEntity, playerLogic);
            engineCM.GetComponent<Ark::GameRole>(elementEntity, elementLogic);

            //Get transform components for player and trigger
            Ark::Transform playerTransform;
            Ark::Transform elementTransform;
            engineCM.GetComponent<Ark::Transform>(playerEntity, playerTransform);
            engineCM.GetComponent<Ark::Transform>(elementEntity, elementTransform);

            //Store positions of player & hazard/goal.
            Ark::vector3D playerPos = playerTransform.GetPos();
            Ark::vector3D elementPos = elementTransform.GetPos();

            //Calculate difference between positions on each axis.
            Ark::vector3D deltaPos(elementPos.x - playerPos.x, elementPos.y - playerPos.y, elementPos.z - playerPos.z);

            //Calculate distance between the two entities.
            float distance = sqrt(pow(deltaPos.x, 2) + pow(deltaPos.y, 2) + pow(deltaPos.z, 2));
            
            //Check if collision has occured between player and a element.
            if (distance < (playerLogic.GetRadius() + elementLogic.GetRadius())) {
                //Process collision
                this->Collision(engineCM, elementLogic.GetRole());

                //Return as game will end if collision has occured.
                return 0;
            }            
        }
    }

    return 0;
}

bool Ark::GameLogicSystem::Collision(Ark::ComponentManager& engineCM, Ark::Role elementType)
{
    //If element is a goal/"Finish point"...
    if (elementType == Ark::Goal) {
        //Indicate that the user won the game.
        MessageBox(NULL, L"Game Over - Success!", L"Game Over - Success!", 0);
    }
    //If element is a hazard...
    else if(elementType == Ark::Hazard){
        //Indicate the user lost the game.
        MessageBox(NULL, L"Game Over - Fail", L"Game Over - Fail", 0);
    }
    else {
        //Unknown element type.
        return false;
    }

    //Load transforms from design save.
    engineCM.LoadTransforms();

    //Switch to design phase.
    *m_gameActive = false;    

    return true;
}

int Ark::GameLogicSystem::Release()
{
    return 0;
}


