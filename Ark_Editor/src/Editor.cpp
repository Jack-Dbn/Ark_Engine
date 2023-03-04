#include "Editor.h"

Editor::Editor(HINSTANCE instHandle, LPCWSTR windowText, LPCWSTR className) : Ark::Win32App(instHandle, windowText, className)
{
}

int Editor::OnInit()
{
	m_engineInst.Initialise(this->m_wndHandle);

	Ark::Entity entityA = m_engineInst.NewEntity();
	Ark::Entity entityB = m_engineInst.NewEntity();

	//Ark::Triangle triangle;
	//Ark::Square plane;
	Ark::Cube cube;

	Ark::Model helmetModel = m_engineInst.CreateModel("Debug/Assets/Models/Helmet.obj", false, true);
	Ark::Material helmetMaterial = m_engineInst.CreateMaterial(L"Debug/Assets/Textures/Helmet.dds");
	Ark::Model cubeModel = m_engineInst.CreateModelEx(cube.vertices, ARRAYSIZE(cube.vertices), cube.indexes, ARRAYSIZE(cube.indexes));
	Ark::Material rubiksMaterial = m_engineInst.CreateMaterial(L"Debug/Assets/Textures/RubikTexture.dds");

	//Entity A
	Ark::Transform entityAtransform(-1, -1, 1.5f);
	m_engineInst.SetComponent<Ark::Transform>(entityA, entityAtransform);
	m_engineInst.SetComponent<Ark::Material>(entityA, rubiksMaterial);
	m_engineInst.SetComponent<Ark::Model>(entityA, cubeModel);

	//Entity B
	Ark::Transform entityBtransform(1.0f, -1, 1.5f);
	entityBtransform.Rotate(0.0f, 90.0f, 0.0f);
	m_engineInst.SetComponent<Ark::Transform>(entityB, entityBtransform);
	m_engineInst.SetComponent<Ark::Material>(entityB, helmetMaterial);
	m_engineInst.SetComponent<Ark::Model>(entityB, helmetModel);

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

