#pragma once
#include <Windows.h>
#include "WindowApp.h"
#include "GameEngine.h"

class Editor : public Ark::WindowApp
{
public:

	Editor(HINSTANCE instHandle, LPCWSTR windowText = L"", LPCWSTR className = L"Window Class Name");

	//App Stages
	int OnInit();
	int OnUpdate();
	int OnDestroy();

	//App Events
	void Resize(int newHeight, int newWidth);
	void KeyDown(int key);
	void KeyUp(int key);

private:
	Ark::GameEngine m_engineInst;
};

