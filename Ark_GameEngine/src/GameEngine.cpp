#include "GameEngine.h"

namespace Ark {
	GameEngine::GameEngine()
	{
	}

	void GameEngine::Initialise(HWND windowHWND)
	{		
		m_renderSystem.SetHWND(windowHWND);
		m_renderSystem.Initialise();

		Entity::Init();		

		/*
		wchar_t text[256];

		swprintf_s(text, L"%d", cube.m_id);
		MessageBox(NULL, text, text, 0);*/		
	}

	void GameEngine::Update()
	{		
		m_renderSystem.Update();
	}

	void GameEngine::Release()
	{
		m_renderSystem.Release();
	}

	void GameEngine::LoadScene(Scene tgtScene)
	{
		std::vector<Entity> newActiveEntities = tgtScene.GetEntityList();
		
		Entity::UnloadAll();

		for (int e = 0; e < newActiveEntities.size(); e++) {
			newActiveEntities.at(e).Load();
		}
	}

	void GameEngine::WindowResize(int newHeight, int newWidth)
	{
		m_renderSystem.Resize(newHeight, newWidth);
	}
}