#include "EnginePch.h"
#include "Viewport.h"

Viewport::Viewport()
{
}

Viewport::Viewport(float width, float height, float x, float y, float minDepth, float maxDepth)
{
}

Viewport::~Viewport()
{
}

void Viewport::SetViewport()
{
	DEVICE->
}

void Viewport::Set(float width, float height, float x, float y, float minDepth, float maxDepth)
{
	_viewport.TopLeftX = x;
	_viewport.TopLeftY = y;
	_viewport.Width = width;
	_viewport.Height = height;
	_viewport.MinDepth = minDepth;
	_viewport.MaxDepth = maxDepth;
}
