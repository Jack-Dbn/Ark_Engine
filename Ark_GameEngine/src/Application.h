#pragma once
#include "Window.h"

namespace Ark {

	class Application
	{
	public:
		virtual int Run() = 0;

	private:
		Ark::Window* appWindow = nullptr;
	};
}


