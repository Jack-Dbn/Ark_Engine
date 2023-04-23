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

		//Register components to use in the engine.
		m_componentManager.RegisterComponent<Transform>();	
		m_componentManager.RegisterComponent<Model>();
		m_componentManager.RegisterComponent<Material>();
		m_componentManager.RegisterComponent<InputRig>();

		m_renderSystem.SetParam(windowHWND, assetFolderPath);
		m_renderSystem.Initialise(&m_gameActive);
		{
			m_renderSystem.AddReqComponent<Transform>(m_componentManager.GetRegister());
			m_renderSystem.AddReqComponent<Model>(m_componentManager.GetRegister());
			m_renderSystem.AddReqComponent<Material>(m_componentManager.GetRegister());
		}

		m_inputSystem.SetCamera(m_renderSystem.GetCamera());
		m_inputSystem.SetDeltaTime(&m_deltaTime);
		m_inputSystem.Initialise(&m_gameActive);
		{
			m_inputSystem.AddReqComponent<Transform>(m_componentManager.GetRegister());
			m_inputSystem.AddReqComponent<InputRig>(m_componentManager.GetRegister());
		}
		
		wchar_t text[256];

		swprintf_s(text, L"Registered Components: %d", m_componentManager.GetRegisterCount());
		MessageBox(NULL, text, text, 0);		
	}

	void GameEngine::Update()
	{	
		//Delta time calculation
		m_lastTickCount = m_newTickCount;
		m_newTickCount = ::GetTickCount();

		m_deltaTime = (m_newTickCount - m_lastTickCount) / 1000.0f;


		//Input System
		std::vector<Ark::Entity> sysEntities = m_entityManager.EvalSysEntities(m_inputSystem.GetFilterMask());
		m_inputSystem.SetEntityList(sysEntities);

		m_inputSystem.Update(m_componentManager);

		//Render System
		sysEntities = m_entityManager.EvalSysEntities(m_renderSystem.GetFilterMask());
		m_renderSystem.SetEntityList(sysEntities);

		m_renderSystem.Update(m_componentManager);
	}

	void GameEngine::Release()
	{
		m_inputSystem.Release();
		m_renderSystem.Release();
	}

	void GameEngine::WindowResize(int newHeight, int newWidth)
	{
		m_renderSystem.Resize(newHeight, newWidth);
	}

	void GameEngine::KeyUp(int key)
	{
		m_inputSystem.KeyUp(key);
	}

	void GameEngine::KeyDown(int key)
	{
		m_inputSystem.KeyDown(key);
	}

	Ark::EntityManager* GameEngine::GetEC()
	{
		return &m_entityManager;
	}

	Ark::Entity GameEngine::NewEntity()
	{
		return m_entityManager.NewEntity();
	}

	Ark::Model GameEngine::CreateModelEx(void* vtxArray,
		unsigned int vtxArraySize,
		unsigned int* idxArray,
		unsigned int idxArraySize)
	{
		return m_renderSystem.CreateDxModelEx(vtxArray, vtxArraySize, idxArray, idxArraySize);
	}

	Ark::Model GameEngine::CreateModel(std::string filePath, bool CwWindingDir, bool LH_Convert)
	{
		return m_renderSystem.CreateDxModel(filePath, CwWindingDir, LH_Convert);
	}

	Ark::Material GameEngine::CreateMaterial(std::wstring textureFilePath)
	{
		return m_renderSystem.CreateMaterial(textureFilePath);
	}
}