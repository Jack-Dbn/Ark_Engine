#pragma once
#include <unordered_map>

namespace Ark {

//Axis to apply transformation.
enum Axis {
	x = 0,
	y = 1,
	z = 2
};

//Transform to apply.
enum Transformation {
	Position = 0,
	Rotation = 1,
	Scale = 2
};

//Struct to encompass action related fields.
struct Action {
	Transformation action;
	Axis axis;
	float inputSize;
};

class InputRig
{
public:
	InputRig();

	//For editor to define input rig's controls and actions.
	bool SetPositionInput(char key, Axis axis, float inputSize);
	bool SetRotationInput(char key, Axis axis, float inputSize);
	bool SetScaleInput(char key, Axis axis, float inputSize);

	//For input system to access keys mapped.
	std::unordered_map<char, Action> GetKeyMap();

private:
	//Stores keyboard keys against their action.
	std::unordered_map<char, Action> m_keyMap;
};

}