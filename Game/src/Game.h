#pragma once
#include <Windows.h>
#include "Win32App.h"
#include "GameEngine.h"

class Game : public Ark::Win32App
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

