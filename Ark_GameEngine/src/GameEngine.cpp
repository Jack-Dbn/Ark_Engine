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

		//cube.Load();
		//cube2.Load();

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