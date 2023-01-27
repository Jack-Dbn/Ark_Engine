#include "Editor.h"

Editor::Editor(HINSTANCE instHandle, LPCWSTR windowText, LPCWSTR className) : Ark::Win32App(instHandle, windowText, className)
{
}

int Editor::OnInit()
{
	m_engineInst.Initialise(this->m_wndHandle);

	Ark::Entity entityA = m_engineInst.GetEC()->NewEntity();
	Ark::Entity entityB = m_engineInst.GetEC()->NewEntity();
	Ark::Entity entityC = m_engineInst.GetEC()->NewEntity();
	Ark::Entity entityD = m_engineInst.GetEC()->NewEntity();

	Ark::Transform entityAtransform;
	entityAtransform.ChangePos(2, -1, 2);
	m_engineInst.GetCM()->AddComponent<Ark::Transform>(entityA, entityAtransform);

	Ark::Transform entityBtransform;
	entityBtransform.ChangePos(3, 7, 3);
	m_engineInst.GetCM()->AddComponent<Ark::Transform>(entityB, entityBtransform);

	Ark::Transform entityCtransform;
	entityCtransform.ChangePos(1, 2, 5);
	m_engineInst.GetCM()->AddComponent<Ark::Transform>(entityC, entityCtransform);

	Ark::Transform entityDtransform;
	entityDtransform.ChangePos(2, 2, 2);
	m_engineInst.GetCM()->AddComponent<Ark::Transform>(entityD, entityDtransform);

	m_engineInst.GetCM()->RemoveComponent<Ark::Transform>(entityA);

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

