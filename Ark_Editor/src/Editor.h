#pragma once
#include <Windows.h>
#include "Application.h"

class Editor : public Ark::Application
{
public:
	//Application States
	void OnCreate();
	void OnUpdate();
	void OnDelete();

};

