#include "InputRig.h"

Ark::InputRig::InputRig()
{
}

bool Ark::InputRig::SetPositionInput(char key, Axis axis, float inputSize)
{
	Action newAction;
	newAction.action = Position;
	newAction.axis = axis;
	newAction.inputSize = inputSize;

	m_keyMap[key] = newAction;

	return true;
}

bool Ark::InputRig::SetRotationInput(char key, Axis axis, float inputSize)
{
	Action newAction;
	newAction.action = Rotation;
	newAction.axis = axis;
	newAction.inputSize = inputSize;

	m_keyMap[key] = newAction;

	return true;
}

bool Ark::InputRig::SetScaleInput(char key, Axis axis, float inputSize)
{
	Action newAction;
	newAction.action = Scale;
	newAction.axis = axis;
	newAction.inputSize = inputSize;

	m_keyMap[key] = newAction;

	return true;
}

std::unordered_map<char, Ark::Action> Ark::InputRig::GetKeyMap()
{
	return m_keyMap;
}
