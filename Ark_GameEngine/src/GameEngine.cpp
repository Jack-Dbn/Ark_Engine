#include "GameEngine.h"

namespace Ark {
	GameEngine::GameEngine()
	{
	}

	void GameEngine::Initialise(HWND windowHWND, std::wstring assetFolderPath)
	{
		m_deltaTime = 0.0f;
		m_lastTickCount = 0;
		m_newTickCount = 0;

		m_gameActive = false;

		//Register components so they can be used in the engine.
		m_componentManager.RegisterComponent<Transform>();	
		m_componentManager.RegisterComponent<Model>();
		m_componentManager.RegisterComponent<Material>();
		m_componentManager.RegisterComponent<InputRig>();
		m_componentManager.RegisterComponent<GameRole>();

		//Set window handle and location of assets.
		m_graphicsSystem.SetParam(windowHWND, assetFolderPath);
		m_graphicsSystem.Initialise(&m_gameActive);
		{
			//State which components are required by this system.
			m_graphicsSystem.AddReqComponent<Transform>(m_componentManager.GetRegister());
			m_graphicsSystem.AddReqComponent<Model>(m_componentManager.GetRegister());
			m_graphicsSystem.AddReqComponent<Material>(m_componentManager.GetRegister());
		}

		//Set input system to use graphics system's camera.
		m_inputSystem.SetCamera(m_graphicsSystem.GetCamera());
		m_inputSystem.SetDeltaTime(&m_deltaTime);
		m_inputSystem.Initialise(&m_gameActive);
		{
			//State which components are required by this system.
			m_inputSystem.AddReqComponent<Transform>(m_componentManager.GetRegister());
			m_inputSystem.AddReqComponent<InputRig>(m_componentManager.GetRegister());
		}

		m_gameplaySystem.Initialise(&m_gameActive);
		{
			//State which components are required by this system.
			m_gameplaySystem.AddReqComponent<Transform>(m_componentManager.GetRegister());
			m_gameplaySystem.AddReqComponent<GameRole>(m_componentManager.GetRegister());
		}
		
		//Debugging code
		/*
		wchar_t text[256];

		swprintf_s(text, L"Registered Components: %d", m_componentManager.GetRegisterCount());
		MessageBox(NULL, text, text, 0);*/
	}

	void GameEngine::Update()
	{	
		//Delta time calculation
		m_lastTickCount = m_newTickCount;
		m_newTickCount = ::GetTickCount();

		m_deltaTime = (m_newTickCount - m_lastTickCount) / 1000.0f;

		//Gameplay System
		std::vector<Ark::Entity> sysEntities = m_entityManager.EvalSysEntities(m_gameplaySystem.GetFilterMask());
		m_gameplaySystem.SetEntityList(sysEntities);

		m_gameplaySystem.Update(m_componentManager);

		//Input System
		sysEntities = m_entityManager.EvalSysEntities(m_inputSystem.GetFilterMask());
		m_inputSystem.SetEntityList(sysEntities);

		m_inputSystem.Update(m_componentManager);

		//Render System
		sysEntities = m_entityManager.EvalSysEntities(m_graphicsSystem.GetFilterMask());
		m_graphicsSystem.SetEntityList(sysEntities);

		m_graphicsSystem.Update(m_componentManager);
	}

	void GameEngine::Release()
	{
		m_gameplaySystem.Release();
		m_inputSystem.Release();
		m_graphicsSystem.Release();
	}

	//Pass events to the relevant systems.
	void GameEngine::WindowResize(int newHeight, int newWidth)
	{
		m_graphicsSystem.Resize(newHeight, newWidth);
	}

	void GameEngine::KeyUp(int key)
	{
		m_inputSystem.KeyUp(key);
	}

	void GameEngine::KeyDown(int key)
	{
		m_inputSystem.KeyDown(key);
	}

	//To allow editor to create new entities
	Ark::EntityManager* GameEngine::GetEC()
	{
		return &m_entityManager;
	}

	Ark::Entity GameEngine::NewEntity()
	{
		return m_entityManager.NewEntity();
	}

	//Graphics System - Use Cases
	Ark::Model GameEngine::CreateModelEx(void* vtxArray,
		unsigned int vtxArraySize,
		unsigned int* idxArray,
		unsigned int idxArraySize)
	{
		return m_graphicsSystem.CreateDxModelEx(vtxArray, vtxArraySize, idxArray, idxArraySize);
	}

	Ark::Model GameEngine::CreateModel(std::string filePath, bool CwWindingDir, bool LH_Convert)
	{
		return m_graphicsSystem.CreateDxModel(filePath, CwWindingDir, LH_Convert);
	}

	Ark::Material GameEngine::CreateMaterial(std::wstring textureFilePath)
	{
		return m_graphicsSystem.CreateMaterial(textureFilePath);
	}
}