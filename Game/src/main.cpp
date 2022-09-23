#include <iostream>
#include "Game.h"

int WINAPI wWinMain(HINSTANCE instHandle, HINSTANCE prevInstHandle, PWSTR cmdLineArgs, int displayMode) {

	Game usersGame(instHandle, L"Game Powered By Ark", L"Game Window");

	return usersGame.Run();
}