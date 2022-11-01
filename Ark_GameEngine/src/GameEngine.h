#pragma once
#include <vector>
#include "GameEngine/Systems/RenderSystem.h"
#include "GameEngine/Components/Transform.h"
#include "GameEngine/EntityController.h"

namespace Ark {	

	class GameEngine
	{
	public:

		GameEngine();
		
		void Initialise(HWND windowHWND);

		void Update();

		void Release();

		void WindowResize(int newHeight, int newWidth);

		Ark::EntityController* GetEC();

	private:
		std::vector<System> m_activeSystems;

		EntityController m_entityController;

		RenderSystem m_renderSystem;
	};
}


