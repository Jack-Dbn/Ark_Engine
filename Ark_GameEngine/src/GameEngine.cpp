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
		
		Entity cube;

		Entity cube2;
		Entity cube3;

		cube.Load();
		cube2.Load();

		/*
		wchar_t text[256];

		swprintf_s(text, L"%d", cube.m_id);
		MessageBox(NULL, text, text, 0);*/

		//Scene mainScene

		//Entity cubeOne
		//Material solidMaterial
		//cubeOne.AddComponent(Component solidMaterial)
		//mainScene.AddEntity(cubeOne)
		//this->LoadScene(mainScene)
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