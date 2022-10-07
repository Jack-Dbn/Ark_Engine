#pragma once
#include "..\Component.h"

class Material : public Component
{
public:
	Material();

private:
	float m_colour[4];
};

