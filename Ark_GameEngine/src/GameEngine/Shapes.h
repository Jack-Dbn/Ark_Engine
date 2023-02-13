#pragma once
#include "Math.h"

namespace Ark {
struct Square {
	Ark::vertex vertices[4] =
	{
		{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f,  -0.5f}, {0.0f, 1.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f, 0.5f}, {1.0f, 1.0f, 0.0f}}
	};
	unsigned int indexes[6] =
	{
		2, 1, 0,
		3, 2, 0
	};
};

struct Triangle {
	Ark::vertex vertices[3] =
	{
		{{-0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
		{{0.0f,  0.5f}, {0.0f, 1.0f, 1.0f}},
		{{0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}}
	};
	unsigned int indexes[3] =
	{
		0, 1, 2
	};
};

/*
struct Cube {
	Ark::vertex vertices[8] =
	{
		{{-0.5f, -0.5f, -0.5f},{1.0f, 0.5f, 0.0f}},
		{{-0.5f,  0.5f, -0.5f},{1.0f, 0.5f, 0.0f}},
		{{0.5f, 0.5f, -0.5f}, {1.0f, 0.5f, 0.0f}},
		{{0.5f, -0.5f, -0.5f}, {1.0f, 0.5f, 0.0f}},

		{{0.5f, -0.5f, 0.5f},{1.0f, 0.5f, 0.0f}},
		{{0.5f,  0.5f, 0.5f},{1.0f, 0.5f, 0.0f}},
		{{-0.5f, 0.5f, 0.5f}, {1.0f, 0.5f, 0.0f}},
		{{-0.5f, -0.5f, 0.5f}, {1.0f, 0.5f, 0.0f}}
	};
	unsigned int indexes[36] =
	{		
		0,1,2,  
		2,3,0, 
		
		4,5,6,
		6,7,4,
		
		1,6,5,
		5,2,1,
		
		7,0,3,
		3,4,7,
		
		3,2,5,
		5,4,3,
		
		7,6,1,
		1,0,7
	};
};*/
}