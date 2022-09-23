#pragma once
#include <Windows.h>

namespace Ark {

	class Win32App
	{
	public:
		Win32App(HINSTANCE instHandle, LPCWSTR windowText = L"", LPCWSTR className = L"Window Class Name");

		int Run(int displayMode = SW_NORMAL);

		

		//App Events
		virtual void Resize() = 0;

		bool wndActive = false;

	protected:
		//App Stages
		//virtual int OnInit() = 0;
		virtual int OnUpdate() = 0;
		virtual int OnDestroy() = 0;

		HWND wndHandle = NULL;		

		WNDCLASS wndClass = {};

		LPCWSTR wndText = L"";
		long wndStyle = WS_OVERLAPPEDWINDOW;

		int width = CW_USEDEFAULT, height = CW_USEDEFAULT, posX = CW_USEDEFAULT, posY = CW_USEDEFAULT;

	private:
		bool DisplayWindow(int displayMode);
	};
}


