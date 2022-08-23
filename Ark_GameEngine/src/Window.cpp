#include "Window.h"

namespace Ark {

	LRESULT CALLBACK WindowProc(HWND wndHandle, UINT wndMsg, WPARAM wParam, LPARAM lParam) {

		Application* linkedApp = reinterpret_cast<Application*>(GetWindowLongPtr(wndHandle, GWLP_USERDATA));

		switch (wndMsg) {

			case WM_CREATE:
				{
					LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
					SetWindowLongPtr(wndHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));

					Application* linkedApp = reinterpret_cast<Application*>(GetWindowLongPtr(wndHandle, GWLP_USERDATA));
					if (linkedApp) {
						linkedApp->OnCreate();
					}
				}
				return 0;

			case WM_PAINT:
				
				if (linkedApp) {
					linkedApp->OnUpdate();
				}
				if(true) {
					PAINTSTRUCT paintStruct;
					HDC hdc = BeginPaint(wndHandle, &paintStruct);

					// All painting occurs here, between BeginPaint and EndPaint.

					FillRect(hdc, &paintStruct.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

					EndPaint(wndHandle, &paintStruct);
				}
				return 0;

			case WM_DESTROY:
				if (linkedApp) {
					linkedApp->OnDelete();
				}
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

	int Window::LinkApp(Application* targetApp)
	{
		this->linkedApp = targetApp;

		return 0;
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
			this->width, this->height, this->posX, this->posY,

			NULL,
			NULL,
			this->wndClass.hInstance,
			this->linkedApp //Change to external app
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

