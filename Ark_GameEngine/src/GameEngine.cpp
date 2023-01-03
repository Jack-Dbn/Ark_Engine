#include "GameEngine.h"

namespace Ark {
	GameEngine::GameEngine()
	{
	}

	void GameEngine::Initialise(HWND windowHWND)
	{		
		m_renderSystem.SetHWND(windowHWND);
		m_renderSystem.Initialise();

		m_componentManager.RegisterComponent<Transform>();
		
		Entity entityA = m_entityController.NewEntity();
		Entity entityB = m_entityController.NewEntity();

		Transform entityAtransform;
		entityAtransform.ChangePos(2, -1, 2);
		m_componentManager.AddComponent<Transform>(entityA, entityAtransform);

		Transform entityBtransform;
		entityBtransform.ChangePos(3, 7, 3);
		m_componentManager.AddComponent<Transform>(entityB, entityBtransform);

		Transform recordTransform;
		m_componentManager.GetComponent<Transform>(entityA, recordTransform);


		wchar_t text[256];

		swprintf_s(text, L"Registered Components: %d", m_componentManager.GetRegisterCount());
		MessageBox(NULL, text, text, 0);

		swprintf_s(text, L"Total Entities: %d", m_entityController.GetEntityCount());
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