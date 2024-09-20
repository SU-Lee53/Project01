#include "EnginePch.h"
#include "Viewport.h"

Viewport::Viewport()
{
	Set(800, 600);
}

Viewport::Viewport(float width, float height, float x, float y, float minDepth, float maxDepth)
{
	Set(width, height, x, y, minDepth, maxDepth);
}

Viewport::~Viewport()
{
}

void Viewport::SetViewport()
{
	DC->RSSetViewports(1, &_viewport);
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
