#pragma once
#include "../System.h"
#include "../Components/GameRole.h"

namespace Ark {
	class GameLogicSystem : public System
	{
	public:
		GameLogicSystem();

		//System stages
		int Initialise(bool* isGameRunning);
		int Update(Ark::ComponentManager& engineCM);
		int Release();

	private:
		//Handle collision response.
		bool Collision(Ark::ComponentManager& engineCM, Ark::Role triggerType);

		bool* m_gameActive;
	};
}


