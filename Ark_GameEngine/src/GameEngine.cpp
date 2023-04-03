#include "GameEngine.h"

namespace Ark {
	GameEngine::GameEngine()
	{
	}

	void GameEngine::Initialise(HWND windowHWND, std::wstring assetFolderPath)
	{				
		//Register components to use in the engine.
		m_componentManager.RegisterComponent<Transform>();	
		m_componentManager.RegisterComponent<Model>();
		m_componentManager.RegisterComponent<Material>();

		m_renderSystem.SetParam(windowHWND, assetFolderPath);
		m_renderSystem.Initialise();
		{
			m_renderSystem.AddReqComponent<Transform>(m_componentManager.GetRegister());
			m_renderSystem.AddReqComponent<Model>(m_componentManager.GetRegister());
			m_renderSystem.AddReqComponent<Material>(m_componentManager.GetRegister());
		}

		m_inputSystem.Initialise();
		{
			m_inputSystem.AddReqComponent<Transform>(m_componentManager.GetRegister());
		}
		
		wchar_t text[256];

		swprintf_s(text, L"Registered Components: %d", m_componentManager.GetRegisterCount());
		MessageBox(NULL, text, text, 0);		
	}

	void GameEngine::Update()
	{	
		//Input System
		std::vector<Ark::Entity> sysEntities = m_entityController.EvalSysEntities(m_inputSystem.GetFilterMask());
		m_inputSystem.SetEntityList(sysEntities);

		m_inputSystem.Update(m_componentManager);

		//Render System
		sysEntities = m_entityController.EvalSysEntities(m_renderSystem.GetFilterMask());
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

	Ark::EntityController* GameEngine::GetEC()
	{
		return &m_entityController;
	}

	Ark::Entity GameEngine::NewEntity()
	{
		return m_entityController.NewEntity();
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