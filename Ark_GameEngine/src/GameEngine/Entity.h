#pragma once
class Entity
{
public:
	Entity();

	unsigned int GetId();

private:
	static unsigned int m_IdCounter;

	unsigned int m_Id;

	bool m_ComponentMask[];
};

