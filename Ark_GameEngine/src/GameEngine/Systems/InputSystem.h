#pragma once
#include "../System.h"

class InputSystem
{
public:
	InputSystem();

	int Initialise();
	int Update(Ark::ComponentManager& engineCM);
	int Release();
};

