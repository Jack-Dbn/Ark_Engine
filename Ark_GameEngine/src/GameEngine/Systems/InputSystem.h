#pragma once
#include "../System.h"
#include "../Systems/GraphicsSystem/Camera.h"
#include "../Components/InputRig.h"

class InputSystem : public System
{
public:
	InputSystem();

	bool SetCamera(Ark::Camera* camera);
	bool SetDeltaTime(float* deltaTimePtr);

	int Initialise();
	int Update(Ark::ComponentManager& engineCM);
	int Release();

	//Events
	void KeyUp(int keyCode);
	void KeyDown(int keyCode);

private:
	void PreviewInput(int keyCode);
	void GameInput(int keyCode);

	void RigInput(int keyCode, Ark::ComponentManager& engineCM);

	bool m_designPreview;

	std::unordered_map<int, bool> m_keyMap;

	Ark::Camera* m_engineCamera;

	int m_screenHeight, m_screenWidth;

	float m_mouseSensitivity;
	float m_cameraSpeed;

	float* m_engineDeltaTime;
};

