#include "GameEngine.h"

namespace Ark {
	GameEngine::GameEngine()
	{
	}

	void GameEngine::Initialise(HWND windowHWND)
	{		
		m_renderSystem.SetHWND(windowHWND);
		m_renderSystem.Initialise();

		//Register components to use in the engine.
		m_componentManager.RegisterComponent<Transform>();	
		
		wchar_t text[256];

		swprintf_s(text, L"Registered Components: %d", m_componentManager.GetRegisterCount());
		MessageBox(NULL, text, text, 0);		
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

	Ark::EntityController* GameEngine::GetEC()
	{
		return &m_entityController;
	}

	Ark::ComponentManager* GameEngine::GetCM()
	{
		return &m_componentManager;
	}
}