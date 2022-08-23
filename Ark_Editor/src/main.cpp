#include <iostream>
#include "Window.h"

int WINAPI wWinMain(HINSTANCE instHandle, HINSTANCE prevInstHandle, PWSTR cmdLineArgs, int displayMode) {

	Ark::Window editorWindow(instHandle, L"Ark Editor", L"Editor Window");

	editorWindow.Show();

	return 0;
}