#pragma once
#include <Windows.h>
#include "WindowApp.h"
#include "GameEngine.h"
#include "GameEngine/include/imgui/imgui.h"
#include "GameEngine/include/imgui/imgui_impl_win32.h"
#include "GameEngine/include/imgui/imgui_impl_dx11.h"

class Editor : public Ark::WindowApp
{
public:
	//Constructor
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
	//Instance of game engine.
	Ark::GameEngine m_gameEngine;
};

