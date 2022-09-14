#pragma once
#include <Windows.h>

namespace Ark {
	class Window
	{
	public:
		Window(HINSTANCE instHandle, LPCWSTR windowText = L"", LPCWSTR className = L"Window Class Name");

		int Show(int displayMode = SW_NORMAL, bool loopFlag = false);

		int CheckMsgQueue();

		bool IsActive();

		void Release();

	private:

		WNDCLASS wndClass = {};
		bool wndActive = false;

		LPCWSTR wndText = L"";
		long wndStyle = WS_OVERLAPPEDWINDOW;

		int width = CW_USEDEFAULT, height = CW_USEDEFAULT, posX = CW_USEDEFAULT, posY = CW_USEDEFAULT;

	};
}


