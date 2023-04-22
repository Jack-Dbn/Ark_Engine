#pragma once
#include <unordered_map>

namespace Ark {

enum Axis {
	x = 0,
	y = 1,
	z = 2
};

enum Transformation {
	Position = 0,
	Rotation = 1,
	Scale = 2
};

struct Action {
	Transformation action;
	Axis axis;
	float inputSize;
};

class InputRig
{
public:
	InputRig();

	bool SetPositionInput(char key, Axis axis, float inputSize);
	bool SetRotationInput(char key, Axis axis, float inputSize);
	bool SetScaleInput(char key, Axis axis, float inputSize);

	std::unordered_map<char, Action> GetKeyMap();

private:
	std::unordered_map<char, Action> m_keyMap;
};

}