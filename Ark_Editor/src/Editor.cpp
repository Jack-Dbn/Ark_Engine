#include "Editor.h"

Editor::Editor(HINSTANCE instHandle, LPCWSTR windowText, LPCWSTR className) : Ark::Win32App(instHandle, windowText, className)
{
	MessageBox(NULL, L"Editor Constructed", L"Editor Constructed", 0);
}

int Editor::OnUpdate()
{
	MessageBox(NULL, L"Editor OnUpdate", L"Editor OnUpdate", 0);
	return 0;
}

int Editor::OnDestroy()
{
	MessageBox(NULL, L"Editor OnDestroy", L"Editor OnDestroy", 0);
	return 0;
}

void Editor::Resize()
{
	MessageBox(NULL, L"Editor Resize", L"Editor Resize", 0);
}

