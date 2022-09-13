#include "RenderSystem.h"

// Constructor
RenderSystem::RenderSystem()
{
	MessageBox(NULL, L"RenderSystem Created", L"Constructor", 0);
}

// Initialise Stage
void RenderSystem::Initialise()
{
	MessageBox(NULL, L"RenderSystem Initialised", L"Init", 0);
}

// Update Stage
void RenderSystem::Update()
{
}

// Release Stage
void RenderSystem::Release()
{
	MessageBox(NULL, L"RenderSystem Released", L"Release", 0);
}


