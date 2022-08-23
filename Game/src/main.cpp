#include <iostream>
#include "Window.h"


int WINAPI wWinMain(HINSTANCE instHandle, HINSTANCE prevInstHandle, PWSTR cmdLineArgs, int displayMode) {

	Ark::Window gameWindow(instHandle, L"Game Powered By Ark", L"Game Window");

	gameWindow.Show();

	return 0;
}