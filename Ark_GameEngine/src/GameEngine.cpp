#include "GameEngine.h"

namespace Ark {
	GameEngine::GameEngine()
	{
	}

	void GameEngine::Initialise(HWND windowHWND)
	{		
		m_renderSystem.SetHWND(windowHWND);
		m_renderSystem.Initialise();
	}

	void GameEngine::Update()
	{		
		m_renderSystem.Update();
	}

	void GameEngine::Release()
	{
		m_renderSystem.Release();
	}

	void GameEngine::WindowResize(int newHeight, int newWidth)
	{
		m_renderSystem.Resize(newHeight, newWidth);
	}
}