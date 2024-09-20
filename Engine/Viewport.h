#pragma once

class Viewport
{
public:
	Viewport(float width, float height, float x = 0, float y = 0, float minDepth = 0, float maxDepth = 0);
	~Viewport();

public:
	void SetViewport();
	
public:
	void Set(float width, float height, float x, float y, float minDepth, float maxDepth);

private:
	D3D11_VIEWPORT _viewport;

};

