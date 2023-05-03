#include "WindowApp.h"

namespace Ark {

	float windowHeight, windowWidth;

	LRESULT CALLBACK WindowProc(HWND wndHandle, UINT wndMsg, WPARAM wParam, LPARAM lParam) {

		//Create pointer to the WindowApp instance calling this procedure.
		WindowApp* tgtApp = reinterpret_cast<WindowApp*>(GetWindowLongPtr(wndHandle, GWLP_USERDATA));

		switch (wndMsg) {

		//When window is created...
		case WM_CREATE:
			{
				//Initialise WindowApp pointer.
				LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
				SetWindowLongPtr(wndHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));
			}
			return 0;

		//When right-click pressed...
		case WM_RBUTTONDOWN:
			::ShowCursor(false);
			tgtApp->KeyDown(VK_RBUTTON);
			return 0;

		//When right-click released...
		case WM_RBUTTONUP:
			::ShowCursor(true);
			tgtApp->KeyUp(VK_RBUTTON);
			return 0;

		//When keyboard-key is down...
		case WM_KEYDOWN:
			tgtApp->KeyDown((int)wParam);
			return 0;

		//When keyboard-key is released...
		case WM_KEYUP:
			tgtApp->KeyUp((int)wParam);
			return 0;
		
		//As windows resized, store the height & width
		case WM_SIZE:

			windowHeight = HIWORD(lParam);
			windowWidth = LOWORD(lParam);

			return 0;

		//Trigger event method when resizing is finished.
		case WM_EXITSIZEMOVE:

			tgtApp->Resize(windowHeight, windowWidth);

			return 0;

		//Set boolean to false to exit update loop.
		case WM_DESTROY:
			tgtApp->m_WndActive = false;
			return 0;

		default:
			break;
		}

		//If no case triggered, return default response.
		return DefWindowProc(wndHandle, wndMsg, wParam, lParam);
	}

	WindowApp::WindowApp(HINSTANCE instHandle, LPCWSTR windowText, LPCWSTR className)
	{

		WNDCLASS newWndClass = {};

		newWndClass.lpszClassName = className;
		newWndClass.hInstance = instHandle;
		newWndClass.lpfnWndProc = WindowProc;//Set callback above as window procedure to use.

		m_wndClass = newWndClass;
		m_wndText = windowText;//Text thats displayed in header.

		RegisterClass(&m_wndClass);

		//Create Window Handle
		m_wndHandle = CreateWindowEx(
			0,
			m_wndClass.lpszClassName,
			m_wndText,
			m_wndStyle,

			//Size and Position
			m_width, m_height, m_posX, m_posY,

			NULL,
			NULL,
			m_wndClass.hInstance,
			this//Pass through itself so it can call event methods in window proc.
		);
	}

	//Display window to the user.
	bool WindowApp::DisplayWindow(int displayMode)
	{
		//Check handle has been created sucessfully.
		if (m_wndHandle == NULL) {
			return false;
		}

		//Show Window
		ShowWindow(m_wndHandle, displayMode);

		//Set update loop flag to true.
		m_WndActive = true;

		return true;
	}

	int WindowApp::Run(int displayMode)
	{
		//Invoke initialise stage of child class.
		this->OnInit();

		//Show the window to user.
		this->DisplayWindow(displayMode);

		//Queue to store windows messages.
		MSG msgQueue = {};

		//Update Loop, runs whilst window is displayed.
		while (m_WndActive) {

			//While there are windows messages in Queue.
			while (PeekMessage(&msgQueue, NULL, 0, 0, PM_REMOVE)) {

				//Translate and Process messages.
				TranslateMessage(&msgQueue);
				DispatchMessage(&msgQueue);
			}

			//Invoke tick of update stage in child class.
			this->OnUpdate();
		}		

		//Invoke release stage
		this->OnDestroy();

		//Return with no errors recorded.
		return 0;
	}

	//App Events - Not abstract as not every child app class may want to override.
	void WindowApp::Resize(int newHeight, int newWidth)
	{
	}

	void WindowApp::KeyDown(int key)
	{
	}

	void WindowApp::KeyUp(int key)
	{
	}
	
}