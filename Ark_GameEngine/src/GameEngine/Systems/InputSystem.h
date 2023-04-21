#pragma once
#include "../System.h"
#include "../Systems/GraphicsSystem/Camera.h"

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

	bool m_designPreview;

	std::unordered_map<int, bool> m_keyMap;

	Ark::Camera* m_engineCamera;

	int m_screenHeight, m_screenWidth;

	float m_mouseSensitivity;
	float* m_engineDeltaTime;

	//float m_cameraYaw;
	//float m_cameraPitch;
};

