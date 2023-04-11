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
	void PreviewInput(int keyCode);
	void GameInput(int keyCode);

	void TranslateCamera(float x, float y, float z);

	bool m_designPreview;

	std::unordered_map<int, bool> m_keyMap;

	Ark::ConstantBuffer* m_engineCamera;
};

