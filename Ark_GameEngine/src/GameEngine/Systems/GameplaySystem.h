#pragma once
#include "../System.h"
#include "../Components/Logic.h"

namespace Ark {
	class GameplaySystem : public System
	{
	public:
		GameplaySystem();

		int Initialise(bool* isGameRunning);
		int Update(Ark::ComponentManager& engineCM);
		int Release();

	private:
		bool Collision(Ark::ComponentManager& engineCM, Ark::ObjectType triggerType);

		bool* m_gameActive;
	};
}


