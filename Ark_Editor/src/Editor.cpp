#include "Editor.h"

Editor::Editor(HINSTANCE instHandle, LPCWSTR windowText, LPCWSTR className) : Ark::Win32App(instHandle, windowText, className)
{
}

int Editor::OnInit()
{
	m_engineInst.Initialise(this->m_wndHandle);

	Ark::Entity cube = m_engineInst.GetEC()->NewEntity();
	Ark::Entity cube2 = m_engineInst.GetEC()->NewEntity();

	Ark::Transform cubeTransform;
	cubeTransform.ChangePos(1, 1, 1);
	//cube.AddComponent(cubeTransform);

	//MessageBox(NULL, L"Editor OnInit", L"Editor OnInit", 0);
	return 0;
}

int Editor::OnUpdate()
{
	m_engineInst.Update();

	//MessageBox(NULL, L"Editor OnUpdate", L"Editor OnUpdate", 0);
	return 0;
}

int Editor::OnDestroy()
{
	m_engineInst.Release();

	//MessageBox(NULL, L"Editor OnDestroy", L"Editor OnDestroy", 0);
	return 0;
}


void Editor::Resize(int newHeight, int newWidth)
{
	m_engineInst.WindowResize(newHeight, newWidth);
	//MessageBox(NULL, L"Editor Resize", L"Editor Resize", 0);
}

