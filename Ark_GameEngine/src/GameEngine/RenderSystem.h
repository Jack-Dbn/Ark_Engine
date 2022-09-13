#pragma once
#include "System.h"
#include <Windows.h>

class RenderSystem : public System
{
public:
	RenderSystem();

	void Initialise();
	void Update();
	void Release();
};

