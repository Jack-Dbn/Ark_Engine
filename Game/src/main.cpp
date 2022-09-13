#include <iostream>
#include "Window.h"
#include "Game.h"

int WINAPI wWinMain(HINSTANCE instHandle, HINSTANCE prevInstHandle, PWSTR cmdLineArgs, int displayMode) {

	Ark::Window gameWindow(instHandle, L"Game Powered By Ark", L"Game Window");

	Game usersGame(&gameWindow);

	return usersGame.Run();
}