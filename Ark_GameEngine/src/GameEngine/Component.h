#pragma once
class Component
{
public:
	Component();

	virtual int GetMaskPos() = 0;

	virtual void LoadData(int entityPos) = 0;
	virtual void UnloadData(int entityPos) = 0;
};

