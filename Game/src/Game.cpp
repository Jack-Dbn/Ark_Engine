#include "Game.h"

Game::Game(HINSTANCE instHandle, LPCWSTR windowText, LPCWSTR className) : Ark::Win32App(instHandle, windowText, className)
{
	MessageBox(NULL, L"Game Constructed", L"Game Constructed", 0);
}

int Game::OnUpdate()
{
	MessageBox(NULL, L"Game OnUpdate", L"Game OnUpdate", 0);
	return 0;
}

int Game::OnDestroy()
{
	MessageBox(NULL, L"Game OnDestroy", L"Game OnDestroy", 0);
	return 0;
}

void Game::Resize()
{
	MessageBox(NULL, L"Game Resize", L"Game Resize", 0);
}
