#pragma once
#include <vector>
#include "GameEngine/RenderSystem.h"


namespace Ark {
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


