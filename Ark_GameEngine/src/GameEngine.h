#pragma once
#include <vector>
#include "GameEngine/RenderSystem.h"


namespace Ark {
	class GameEngine
	{
	public:
		GameEngine();
		
		void Initialise(HWND windowHWND);

		void Update();

		void Release();

	private:
		std::vector<System> activeSystems;

		RenderSystem renderSystem;
	};
}


