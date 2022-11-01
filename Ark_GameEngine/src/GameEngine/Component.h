#pragma once
class Component
{
public:
	Component();

	virtual int GetMaskPos() = 0;

	virtual void LoadData(unsigned int entityPos) = 0;
	virtual void UnloadData(unsigned int entityPos) = 0;
};

