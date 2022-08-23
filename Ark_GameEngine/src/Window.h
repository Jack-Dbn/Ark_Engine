#pragma once
#include <Windows.h>
#include "Application.h"

namespace Ark {
	class Window
	{
	public:
		Window(HINSTANCE instHandle, LPCWSTR windowText = L"", LPCWSTR className = L"Window Class Name");

		int LinkApp(Application* targetApp);
		int Show(int displayMode = SW_NORMAL);

	private:
		WNDCLASS wndClass = {};
		LPCWSTR wndText = L"";
		long wndStyle = WS_OVERLAPPEDWINDOW;

		int width = CW_USEDEFAULT, height = CW_USEDEFAULT, posX = CW_USEDEFAULT, posY = CW_USEDEFAULT;

		Application* linkedApp = nullptr;
	};
}


