#include <iostream>
#include "Window.h"
#include "Editor.h"

int WINAPI wWinMain(HINSTANCE instHandle, HINSTANCE prevInstHandle, PWSTR cmdLineArgs, int displayMode) {

	Ark::Window editorWindow(instHandle, L"Ark Editor", L"Editor Window");

	Editor editorApp(&editorWindow);

	return editorApp.Run();
}