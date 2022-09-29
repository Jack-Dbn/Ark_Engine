#pragma once
#include <Windows.h>

namespace Ark {

	class Win32App
	{
	public:
		Win32App(HINSTANCE instHandle, LPCWSTR windowText = L"", LPCWSTR className = L"Window Class Name");

		int Run(int displayMode = SW_NORMAL);

		

		//App Events
		virtual void Resize();

		bool m_WndActive = false;

	protected:
		//App Stages
		virtual int OnInit() = 0;
		virtual int OnUpdate() = 0;
		virtual int OnDestroy() = 0;

		HWND m_wndHandle = NULL;		

		WNDCLASS m_wndClass = {};

		LPCWSTR m_wndText = L"";
		long m_wndStyle = WS_OVERLAPPEDWINDOW;

		int m_width = CW_USEDEFAULT, m_height = CW_USEDEFAULT, m_posX = CW_USEDEFAULT, m_posY = CW_USEDEFAULT;

	private:
		bool DisplayWindow(int displayMode);
	};
}


