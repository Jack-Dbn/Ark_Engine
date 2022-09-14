#include "Editor.h"

Editor::Editor(Ark::Window* tgtWindow)
{
	appWindow = tgtWindow;
}

int Editor::Run()
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
