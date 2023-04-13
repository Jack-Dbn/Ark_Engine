#pragma once
#include <Windows.h>
#include "WindowApp.h"
#include "GameEngine.h"

class Game : public Ark::WindowApp
{
public:

	Game(HINSTANCE instHandle, LPCWSTR windowText = L"", LPCWSTR className = L"Window Class Name");

	//App Stages
	int OnInit();
	int OnUpdate();
	int OnDestroy();

	//App Events
	void Resize(int newHeight, int newWidth);

private:
	Ark::GameEngine m_engineInst;
};

