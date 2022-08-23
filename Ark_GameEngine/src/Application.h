#pragma once

namespace Ark {

	class Application
	{
	public:

		//Application States
		virtual void OnCreate() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnDelete() = 0;

		//Application Events
		//virtual void OnKeyDown();
	};
}


