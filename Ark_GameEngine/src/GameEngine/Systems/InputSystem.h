#pragma once
#include "../System.h"
#include "../Systems/RenderSystem/ConstantBuffer.h"

class InputSystem : public System
{
public:
	InputSystem();

	bool SetCamera(Ark::ConstantBuffer* camera);

	int Initialise();
	int Update(Ark::ComponentManager& engineCM);
	int Release();

	//Events
	void KeyUp(int keyCode);
	void KeyDown(int keyCode);

private:
	bool m_designPreview;
	bool m_freeLookEnabled;

	bool m_w, m_s, m_a, m_d;
	bool m_space, m_shift;

	Ark::ConstantBuffer* m_engineCamera;
};

