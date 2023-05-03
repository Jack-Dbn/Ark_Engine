#include <iostream>
#include "Editor.h"

//Entry Point
int WINAPI wWinMain(HINSTANCE instHandle, HINSTANCE prevInstHandle, PWSTR cmdLineArgs, int displayMode) {

	//Create instance of editor application.
	Editor editorApp(instHandle, L"Ark Editor", L"Editor Window");

	//Run the editor application
	return editorApp.Run();//int returned = status code.
}