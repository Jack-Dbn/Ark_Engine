#include "Window.h"

namespace Ark {

	LRESULT CALLBACK WindowProc(HWND wndHandle, UINT wndMsg, WPARAM wParam, LPARAM lParam) {

		switch (wndMsg) {

			case WM_PAINT:
				{
				PAINTSTRUCT pStruct;
				HDC hdc = BeginPaint(wndHandle, &pStruct);

				FillRect(hdc, &pStruct.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

				EndPaint(wndHandle, &pStruct);
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

		this->wndClass = newWndClass;
		this->wndText = windowText;

		RegisterClass(&this->wndClass);
	}

	int Window::Show(int displayMode)
	{
		//Create Window Handle
		HWND wndHandle = CreateWindowEx(
			0,
			this->wndClass.lpszClassName,
			this->wndText,
			this->wndStyle,

			//Size and Position
			this->Width, this->Height, this->PosX, this->PosY,

			NULL,
			NULL,
			this->wndClass.hInstance,
			NULL //Change to external app
		);

		//Check handle has been created sucessfully.
		if (wndHandle == NULL) {
			return -1;
		}

		//Show Window
		ShowWindow(wndHandle, displayMode);

		//Local version of message queue.
		MSG msgQueue = {};

		//Copy window messages to local queue and while messages exist loop...
		while (GetMessage(&msgQueue, wndHandle, 0, 0) > 0) {

			//Translate and Process messages.
			TranslateMessage(&msgQueue);
			DispatchMessage(&msgQueue);
		}

		return 0;
	}

}

