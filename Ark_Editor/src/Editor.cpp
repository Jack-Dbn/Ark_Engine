#include "Editor.h"

Editor::Editor(Ark::Window* tgtWindow)
{
	appWindow = tgtWindow;
}

int Editor::Run()
{
	appWindow->Show();

	while (true) {
		appWindow->CheckMsgQueue();
	}
	
	return 0;
}
