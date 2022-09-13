#pragma once
#include <Windows.h>
#include "Application.h"
#include "GameEngine.h"

class Editor : public Ark::Application
{
public:

	Editor(Ark::Window* tgtWindow);

	//Application Loop
	int Run();

private:
	Ark::Window* appWindow = nullptr;
};

