#pragma once
class System
{
public:
	virtual int Initialise() = 0;
	virtual int Update() = 0;
	virtual int Release() = 0;
};

