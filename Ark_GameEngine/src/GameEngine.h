#pragma once
#include <vector>
#include "GameEngine/Systems/RenderSystem.h"
#include "GameEngine/Components/Transform.h"
#include "GameEngine/Components/Material.h"
#include "GameEngine/Entity.h"

namespace Ark {

	const unsigned int MAX_ENTITIES = 100;

	class GameEngine
	{
	public:
		GameEngine();
		
		void Initialise(HWND windowHWND);

		void Update();

		void Release();

		void WindowResize(int newHeight, int newWidth);

	private:
		std::vector<System> m_activeSystems;

		RenderSystem m_renderSystem;
	};
}


