#pragma once
class System
{
public:
	virtual void Initialise() = 0;
	virtual void Update() = 0;
	virtual void Release() = 0;
};

