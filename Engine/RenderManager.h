#pragma once

class Shader;

class RenderManager
{
public:
	RenderManager();
	~RenderManager();

public:
	shared_ptr<Shader> GetShader() { return _shader; }

private:
	shared_ptr<Shader> _shader;

};

