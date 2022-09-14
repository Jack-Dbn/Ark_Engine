#include "Game.h"

Game::Game(Ark::Window* tgtWindow)
{
	appWindow = tgtWindow;
}

int Game::Run()
{
	appWindow->Show();

	runFlag = true;

	while (runFlag) {
		appWindow->CheckMsgQueue();

		if (!appWindow->IsActive()) {
			runFlag = false;
		}
	}

	return 0;
}
