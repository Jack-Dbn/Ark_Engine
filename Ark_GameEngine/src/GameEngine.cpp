#include "GameEngine.h"

namespace Ark {
	GameEngine::GameEngine()
	{
	}

	void GameEngine::Initialise(HWND windowHWND)
	{		
		renderSystem.SetHWND(windowHWND);
		renderSystem.Initialise();
	}

	void GameEngine::Update()
	{		
		renderSystem.Update();
	}

	void GameEngine::Release()
	{
		renderSystem.Release();
	}
}