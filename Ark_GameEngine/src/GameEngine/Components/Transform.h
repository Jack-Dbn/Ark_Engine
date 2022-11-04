#pragma once
#include <Windows.h>
#include <string>
#include "..\Component.h"

namespace Ark {
	class Transform : public Component
	{
	public:
		Transform();

		void ChangePos(int x = 0, int y = 0, int z = 0);		

	private:
		int m_posX, m_posY, m_posZ;
	};
}


