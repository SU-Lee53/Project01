#pragma once

class Viewport
{
public:
	Viewport();
	Viewport(float width, float height, float x = 0, float y = 0, float minDepth = 0, float maxDepth = 1);
	~Viewport();

public:
	void SetViewport();
	
public:
	void Set(float width, float height, float x = 0, float y = 0, float minDepth = 0, float maxDepth = 1);

private:
	D3D11_VIEWPORT _viewport;

};

