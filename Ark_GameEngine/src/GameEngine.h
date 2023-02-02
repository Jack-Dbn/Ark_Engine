#pragma once
#include <vector>
#include "GameEngine/Systems/RenderSystem.h"
#include "GameEngine/Components/Transform.h"
#include "GameEngine/Components/Model.h"
#include "GameEngine/Components/Material.h"
#include "GameEngine/EntityController.h"
#include "GameEngine/ComponentManager.h"

namespace Ark {	

	class GameEngine
	{
	public:

		GameEngine();
		
		void Initialise(HWND windowHWND, std::wstring assetFolderPath = L"Assets/");

		void Update();

		void Release();

		void WindowResize(int newHeight, int newWidth);

		Ark::EntityController* GetEC();
		Ark::ComponentManager* GetCM();

	private:
		std::vector<System> m_activeSystems;

		EntityController m_entityController;
		ComponentManager m_componentManager;

		RenderSystem m_renderSystem;
	};
}


