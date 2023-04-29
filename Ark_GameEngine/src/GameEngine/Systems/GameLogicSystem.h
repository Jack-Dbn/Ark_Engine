#pragma once
#include "../System.h"
#include "../Components/GameRole.h"

namespace Ark {
	class GameLogicSystem : public System
	{
	public:
		GameLogicSystem();

		int Initialise(bool* isGameRunning);
		int Update(Ark::ComponentManager& engineCM);
		int Release();

	private:
		bool Collision(Ark::ComponentManager& engineCM, Ark::Role triggerType);

		bool* m_gameActive;
	};
}


