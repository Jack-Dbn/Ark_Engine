#include <iostream>
#include "Editor.h"

int WINAPI wWinMain(HINSTANCE instHandle, HINSTANCE prevInstHandle, PWSTR cmdLineArgs, int displayMode) {

	Editor editorApp(instHandle, L"Ark Editor", L"Editor Window");

	return editorApp.Run();
}