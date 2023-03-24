#pragma once
#include <Windows.h>
#include "Win32App.h"
#include "GameEngine.h"

class Editor : public Ark::Win32App
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

