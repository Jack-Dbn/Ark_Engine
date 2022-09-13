#pragma once
#include "GameEngine/RenderSystem.h"

namespace Ark {
	class GameEngine
	{
	public:
		GameEngine();
		
		void Initialise();

		void Update();

		void Release();
	};
}


