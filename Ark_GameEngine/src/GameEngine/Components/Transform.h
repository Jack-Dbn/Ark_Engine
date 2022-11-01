#pragma once
#include <Windows.h>
#include <string>
#include "..\Component.h"

namespace Ark {
	class Transform : public Component
	{
	public:
		static void PrintPos(int entityId);

		Transform();

		int GetMaskPos();

		void LoadData(unsigned int entityPos);
		void UnloadData(unsigned int entityPos);

		void ChangePos(int x = 0, int y = 0, int z = 0);		

	private:
		static const int maskPos = 0;

		static Transform m_activeTransforms[100];

		int m_posX, m_posY, m_posZ;
	};
}


