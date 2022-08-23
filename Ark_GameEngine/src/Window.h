#pragma once
#include <Windows.h>

namespace Ark {
	class Window
	{
	public:
		Window(HINSTANCE instHandle, LPCWSTR windowText = L"", LPCWSTR className = L"Window Class Name");

		int Show(int displayMode = SW_NORMAL);

	private:
		WNDCLASS wndClass = {};
		LPCWSTR wndText = L"";
		long wndStyle = WS_OVERLAPPEDWINDOW;

		int Width = CW_USEDEFAULT, Height = CW_USEDEFAULT, PosX = CW_USEDEFAULT, PosY = CW_USEDEFAULT;
	};
}


