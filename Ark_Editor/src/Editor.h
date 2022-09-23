#pragma once
#include <Windows.h>
#include "Win32App.h"

class Editor : public Ark::Win32App
{
public:

	Editor(HINSTANCE instHandle, LPCWSTR windowText = L"", LPCWSTR className = L"Window Class Name");

	//App Stages
	//OnInit();
	int OnUpdate();
	int OnDestroy();

	//App Events
	void Resize();
};

