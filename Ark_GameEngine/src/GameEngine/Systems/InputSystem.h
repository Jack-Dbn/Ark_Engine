#pragma once
#include "../System.h"
#include "../Systems/GraphicsSystem/Camera.h"
#include "../Components/InputRig.h"

class InputSystem : public System
{
public:
	InputSystem();

	//Set prerequisites 
	bool SetCamera(Ark::Camera* camera);//Allows system to modify graphics system's camera.
	bool SetDeltaTime(float* deltaTimePtr);//Allows system to read engine's delta time.

	//Override system stages
	int Initialise(bool* isGameRunning);
	int Update(Ark::ComponentManager& engineCM);
	int Release();

	//Events
	void KeyUp(int keyCode);
	void KeyDown(int keyCode);

private:
	//Process keyboard inputs for design phase.
	void PreviewInput(int keyCode);
	//Process keyboard inputs for testing phase.
	void GameInput(int keyCode, Ark::ComponentManager& engineCM);

	//Design/Testing phase indicator
	bool* m_gameActive;

	//Store keys that are currently pressed down.
	std::unordered_map<int, bool> m_keyMap;

	//Camera used by the graphics system.
	Ark::Camera* m_engineCamera;

	//Height and width of users screen.
	int m_screenHeight, m_screenWidth;

	//Value to set how fast the camera rotates.
	float m_mouseSensitivity;

	//Value to set how fast the camera translates.
	float m_cameraSpeed;

	//Delta time calculated by engine each frame.
	float* m_engineDeltaTime;
};

