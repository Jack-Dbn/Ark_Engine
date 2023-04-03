#pragma once
#include "../System.h"

class InputSystem : public System
{
public:
	InputSystem();

	int Initialise();
	int Update(Ark::ComponentManager& engineCM);
	int Release();

	//Events
	void KeyUp(int keyCode);
	void KeyDown(int keyCode);

private:
	bool designPreview;
	bool freeLookEnabled;
};

