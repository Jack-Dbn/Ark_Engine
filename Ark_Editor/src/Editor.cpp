#include "Editor.h"

Editor::Editor(HINSTANCE instHandle, LPCWSTR windowText, LPCWSTR className) : Ark::Win32App(instHandle, windowText, className)
{
}

int Editor::OnInit()
{
	m_engineInst.Initialise(this->m_wndHandle);

	Ark::Entity entityA = m_engineInst.NewEntity();
	Ark::Entity entityB = m_engineInst.NewEntity();

	Ark::Triangle triangle;
	Ark::Square square;
	Ark::Cube cube;

	//Entity A
	Ark::Transform entityAtransform(-1, -1, 1.5f);
	m_engineInst.SetComponent<Ark::Transform>(entityA, entityAtransform);
	m_engineInst.AddComponent<Ark::Material>(entityA);

	Ark::Model entityAmodel = m_engineInst.CreateModel(cube.vertices, ARRAYSIZE(cube.vertices), cube.indexes, ARRAYSIZE(cube.indexes));
	m_engineInst.SetComponent<Ark::Model>(entityA, entityAmodel);

	//Entity B
	Ark::Transform entityBtransform(1, -1, 1.5f);
	m_engineInst.SetComponent<Ark::Transform>(entityB, entityBtransform);
	m_engineInst.AddComponent<Ark::Material>(entityB);
	
	Ark::Model entityBmodel = m_engineInst.CreateModel(cube.vertices, ARRAYSIZE(cube.vertices), cube.indexes, ARRAYSIZE(cube.indexes));
	m_engineInst.SetComponent<Ark::Model>(entityB, entityBmodel);

	//MessageBox(NULL, L"Editor OnInit", L"Editor OnInit", 0);

	wchar_t text[256];

	swprintf_s(text, L"Total Entities: %d", m_engineInst.GetEC()->GetEntityCount());
	MessageBox(NULL, text, text, 0);

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

