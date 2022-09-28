#include "Editor.h"

Editor::Editor(HINSTANCE instHandle, LPCWSTR windowText, LPCWSTR className) : Ark::Win32App(instHandle, windowText, className)
{
}

int Editor::OnInit()
{
	engineInst.Initialise(this->wndHandle);

	//MessageBox(NULL, L"Editor OnInit", L"Editor OnInit", 0);
	return 0;
}

int Editor::OnUpdate()
{
	engineInst.Update();

	//MessageBox(NULL, L"Editor OnUpdate", L"Editor OnUpdate", 0);
	return 0;
}

int Editor::OnDestroy()
{
	engineInst.Release();

	//MessageBox(NULL, L"Editor OnDestroy", L"Editor OnDestroy", 0);
	return 0;
}


void Editor::Resize()
{
	//MessageBox(NULL, L"Editor Resize", L"Editor Resize", 0);
}

