#include "Game.h"

Game::Game(HINSTANCE instHandle, LPCWSTR windowText, LPCWSTR className) : Ark::Win32App(instHandle, windowText, className)
{
	//MessageBox(NULL, L"Game Constructed", L"Game Constructed", 0);
}

int Game::OnInit()
{
	m_engineInst.Initialise(this->m_wndHandle);

	//MessageBox(NULL, L"Game OnInit", L"Game OnInit", 0);
	return 0;
}

int Game::OnUpdate()
{
	m_engineInst.Update();

	//MessageBox(NULL, L"Game OnUpdate", L"Game OnUpdate", 0);
	return 0;
}

int Game::OnDestroy()
{
	m_engineInst.Release();

	//MessageBox(NULL, L"Game OnDestroy", L"Game OnDestroy", 0);
	return 0;
}

void Game::Resize(int newHeight, int newWidth)
{
	m_engineInst.WindowResize(newHeight, newWidth);

	//MessageBox(NULL, L"Game Resize", L"Game Resize", 0);
}
