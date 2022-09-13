#include "Window.h"

namespace Ark {

	LRESULT CALLBACK WindowProc(HWND wndHandle, UINT wndMsg, WPARAM wParam, LPARAM lParam) {

		//Application* linkedApp = reinterpret_cast<Application*>(GetWindowLongPtr(wndHandle, GWLP_USERDATA));

		switch (wndMsg) {

			case WM_CREATE:
				{
					//LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
					//SetWindowLongPtr(wndHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));					
				}
				return 0;

			case WM_PAINT:
				if(true) {
					PAINTSTRUCT paintStruct;
					HDC hdc = BeginPaint(wndHandle, &paintStruct);

					// All painting occurs here, between BeginPaint and EndPaint.

					FillRect(hdc, &paintStruct.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

					EndPaint(wndHandle, &paintStruct);
				}
				return 0;

			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;

			default:
				break;
		}

		return DefWindowProc(wndHandle, wndMsg, wParam, lParam);
	}

	Window::Window(HINSTANCE instHandle, LPCWSTR windowText, LPCWSTR className)
	{		
		WNDCLASS newWndClass = {};

		newWndClass.lpszClassName = className;
		newWndClass.hInstance = instHandle;
		newWndClass.lpfnWndProc = WindowProc;

		wndClass = newWndClass;
		wndText = windowText;

		RegisterClass(&wndClass);
	}

	int Window::Show(int displayMode, bool loopFlag)
	{
		//Create Window Handle
		HWND wndHandle = CreateWindowEx(
			0,
			wndClass.lpszClassName,
			wndText,
			wndStyle,

			//Size and Position
			width, height, posX, posY,

			NULL,
			NULL,
			wndClass.hInstance,
			nullptr //Change to external app
		);

		//Check handle has been created sucessfully.
		if (wndHandle == NULL) {
			return -1;
		}
		else {
			handlePtr = &wndHandle;
		}

		//Show Window
		ShowWindow(wndHandle, displayMode);			

		if (loopFlag) {
			//Local version of message queue.
			MSG msgQueue = {};

			//Copy window messages to local queue and while messages exist loop...
			while (GetMessage(&msgQueue, wndHandle, 0, 0) > 0) {

				//Translate and Process messages.
				TranslateMessage(&msgQueue);
				DispatchMessage(&msgQueue);
			}
		}	

		return 0;
	}

	int Window::CheckMsgQueue()
	{
		//Local version of message queue.
		MSG msgQueue = {};

		//Copy window messages to local queue and while messages exist loop...
		while (PeekMessage(&msgQueue, NULL, 0, 0, PM_REMOVE)) {

			//Translate and Process messages.
			TranslateMessage(&msgQueue);
			DispatchMessage(&msgQueue);
		}

		return 0;
	}

}

