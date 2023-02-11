#pragma once
#include "Math.h"

namespace Ark {
struct Square {
	Ark::vector2D vertices[4] =
	{
		{-0.5f, -0.5f},
		{0.5f,  -0.5f},
		{0.5f, 0.5f},
		{-0.5f, 0.5f}
	};
	unsigned int indexes[6] =
	{
		2, 1, 0,
		3, 2, 0
	};
};

struct Triangle {
	Ark::vector2D vertices[3] =
	{
		{-0.5f, -0.5f},
		{0.0f,  0.5f},
		{0.5f, -0.5f}
	};
	unsigned int indexes[3] =
	{
		0, 1, 2
	};
};
}