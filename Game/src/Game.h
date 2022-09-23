#pragma once
#include <Windows.h>
#include "Win32App.h"

class Game : public Ark::Win32App
{
public:

	Game(HINSTANCE instHandle, LPCWSTR windowText = L"", LPCWSTR className = L"Window Class Name");

	//App Stages
	//OnInit();
	int OnUpdate();
	int OnDestroy();

	//App Events
	void Resize();
};

