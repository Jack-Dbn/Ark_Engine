#pragma once
#include <Windows.h>
#include "Application.h"

class Game : public Ark::Application
{
public:
	void OnCreate();
	void OnUpdate();
	void OnDelete();
};

