#pragma once
#include "..\Component.h"

class Transform : public Component
{
public:
	Transform();

private:
	int m_posX, m_posY, m_posZ;
};

