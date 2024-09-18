#pragma once

class Shader;

class RenderManager
{
public:
	RenderManager();
	~RenderManager();

public:
	void Init(shared_ptr<Shader> shader) { _shader = shader; };
	void Update() {}

public:
	shared_ptr<Shader>& GetShader() { return _shader; }

private:
	shared_ptr<Shader> _shader;

};

