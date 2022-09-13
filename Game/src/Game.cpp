#include "Game.h"

Game::Game(Ark::Window* tgtWindow)
{
	appWindow = tgtWindow;
}

int Game::Run()
{
	appWindow->Show();

	while (true) {
		appWindow->CheckMsgQueue();
	}

	return 0;
}
