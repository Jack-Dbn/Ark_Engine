#include "Game.h"

void Game::OnCreate()
{
	MessageBox(NULL, L"Game Created", L"OnCreate", 0);
}

void Game::OnUpdate()
{
}

void Game::OnDelete()
{
	MessageBox(NULL, L"Game Deleted", L"OnDelete", 0);
}
