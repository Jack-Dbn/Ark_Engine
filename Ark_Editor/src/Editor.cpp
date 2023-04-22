#include "Editor.h"

Editor::Editor(HINSTANCE instHandle, LPCWSTR windowText, LPCWSTR className) : Ark::WindowApp(instHandle, windowText, className)
{
}

int Editor::OnInit()
{
	//Initialise Game Engine
	m_gameEngine.Initialise(this->m_wndHandle);

	Ark::Entity entityB = m_gameEngine.NewEntity();
	Ark::Entity entityA = m_gameEngine.NewEntity();

	//Ark::Triangle triangle;
	//Ark::Square plane;
	Ark::Cube cube;

	Ark::Model helmetModel = m_gameEngine.CreateModel("Debug/Assets/Models/Helmet.obj", false, true);
	Ark::Material helmetMaterial = m_gameEngine.CreateMaterial(L"Debug/Assets/Textures/Helmet.dds");
	Ark::Model cubeModel = m_gameEngine.CreateModelEx(cube.vertices, ARRAYSIZE(cube.vertices), cube.indexes, ARRAYSIZE(cube.indexes));
	Ark::Material rubiksMaterial = m_gameEngine.CreateMaterial(L"Debug/Assets/Textures/RubikTexture.dds");

	//Entity A
	Ark::Transform entityAtransform(-1, -1, 1.5f);
	m_gameEngine.SetComponent<Ark::Transform>(entityA, entityAtransform);
	m_gameEngine.SetComponent<Ark::Material>(entityA, rubiksMaterial);
	m_gameEngine.SetComponent<Ark::Model>(entityA, cubeModel);

	Ark::InputRig entityAinputRig;
	entityAinputRig.SetPositionInput(VK_LEFT, Ark::x, 0.05f);
	entityAinputRig.SetPositionInput(VK_RIGHT, Ark::x, -0.05f);
	entityAinputRig.SetPositionInput(VK_UP, Ark::z, 0.05f);
	entityAinputRig.SetPositionInput(VK_DOWN, Ark::z, -0.05f);
	m_gameEngine.SetComponent<Ark::InputRig>(entityA, entityAinputRig);

	//Entity B
	Ark::Transform entityBtransform(1.0f, -1, 1.5f);
	entityBtransform.SetOrientation(0.0f, 90.0f, 0.0f);
	m_gameEngine.SetComponent<Ark::Transform>(entityB, entityBtransform);
	m_gameEngine.SetComponent<Ark::Material>(entityB, helmetMaterial);
	m_gameEngine.SetComponent<Ark::Model>(entityB, helmetModel);

	//MessageBox(NULL, L"Editor OnInit", L"Editor OnInit", 0);

	wchar_t text[256];

	swprintf_s(text, L"Total Entities: %d", m_gameEngine.GetEC()->GetEntityCount());
	MessageBox(NULL, text, text, 0);

	return 0;
}

int Editor::OnUpdate()
{
	//Update Game Engine, Perform tick/render frame
	m_gameEngine.Update();

	//MessageBox(NULL, L"Editor OnUpdate", L"Editor OnUpdate", 0);
	return 0;
}

int Editor::OnDestroy()
{
	//Close Game Engine
	m_gameEngine.Release();

	//MessageBox(NULL, L"Editor OnDestroy", L"Editor OnDestroy", 0);
	return 0;
}


void Editor::Resize(int newHeight, int newWidth)
{
	m_gameEngine.WindowResize(newHeight, newWidth);
	//MessageBox(NULL, L"Editor Resize", L"Editor Resize", 0);
}

void Editor::KeyDown(int key)
{
	m_gameEngine.KeyDown(key);
}

void Editor::KeyUp(int key)
{
	m_gameEngine.KeyUp(key);
}

