#pragma once
#include "../System.h"
#include "../Systems/GraphicsSystem/ConstantBuffer.h"

class InputSystem : public System
{
public:
	InputSystem();

	bool SetCamera(Ark::ConstantBuffer* camera);
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

	void TranslateCamera(float x, float y, float z);

	void RotateCamera(float yaw, float pitch);

	bool m_designPreview;

	std::unordered_map<int, bool> m_keyMap;

	Ark::ConstantBuffer* m_engineCamera;

	int m_screenHeight, m_screenWidth;

	float m_mouseSensitivity;
	float* m_engineDeltaTime;

	float m_cameraYaw;
	float m_cameraPitch;
};

