#pragma once
#include <Windows.h>
#include "Application.h"
#include "GameEngine.h"

class Game : public Ark::Application
{
public:

	Game(Ark::Window* tgtWindow);

	int Run();

private:
	Ark::Window* appWindow = nullptr;
	bool runFlag = false;
};

