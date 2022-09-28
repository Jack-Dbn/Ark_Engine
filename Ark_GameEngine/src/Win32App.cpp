#include "Win32App.h"

namespace Ark {

	LRESULT CALLBACK WindowProc(HWND wndHandle, UINT wndMsg, WPARAM wParam, LPARAM lParam) {

		Win32App* tgtApp = reinterpret_cast<Win32App*>(GetWindowLongPtr(wndHandle, GWLP_USERDATA));

		switch (wndMsg) {

		case WM_CREATE:
		{
			LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
			SetWindowLongPtr(wndHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));
		}
		return 0;

		case WM_PAINT:
			if (true) {
				PAINTSTRUCT paintStruct;
				HDC hdc = BeginPaint(wndHandle, &paintStruct);

				// All painting occurs here, between BeginPaint and EndPaint.

				FillRect(hdc, &paintStruct.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

				EndPaint(wndHandle, &paintStruct);
			}
			return 0;

		case WM_EXITSIZEMOVE:
			tgtApp->Resize();
			return 0;

		case WM_DESTROY:
			tgtApp->wndActive = false;
			//PostQuitMessage(0);
			return 0;

		default:
			break;
		}

		return DefWindowProc(wndHandle, wndMsg, wParam, lParam);
	}

	Win32App::Win32App(HINSTANCE instHandle, LPCWSTR windowText, LPCWSTR className)
	{

		WNDCLASS newWndClass = {};

		newWndClass.lpszClassName = className;
		newWndClass.hInstance = instHandle;
		newWndClass.lpfnWndProc = WindowProc;

		wndClass = newWndClass;
		wndText = windowText;

		RegisterClass(&wndClass);

		//Create Window Handle
		wndHandle = CreateWindowEx(
			0,
			wndClass.lpszClassName,
			wndText,
			wndStyle,

			//Size and Position
			width, height, posX, posY,

			NULL,
			NULL,
			wndClass.hInstance,
			this //Change to external app
		);
	}

	bool Win32App::DisplayWindow(int displayMode)
	{
		//Check handle has been created sucessfully.
		if (wndHandle == NULL) {
			return false;
		}

		//Show Window
		ShowWindow(wndHandle, displayMode);

		wndActive = true;

		return true;
	}

	int Win32App::Run(int displayMode)
	{
		this->OnInit();

		this->DisplayWindow(displayMode);

		//Local version of message queue.
		MSG msgQueue = {};

		while (wndActive) {

			//Copy window messages to local queue and while messages exist loop...
			while (PeekMessage(&msgQueue, NULL, 0, 0, PM_REMOVE)) {

				//Translate and Process messages.
				TranslateMessage(&msgQueue);
				DispatchMessage(&msgQueue);
			}

			this->OnUpdate();
		}		

		this->OnDestroy();

		return 0;
	}

	//App Events
	void Win32App::Resize()
	{
	}
	
}