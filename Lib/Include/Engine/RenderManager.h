#pragma once

class Shader;
class Mesh;

class RenderManager
{
public:
	RenderManager();
	~RenderManager();

public:
	void Init(shared_ptr<Shader> shader) { _shader = shader; };
	void Update() {}
	void Render(shared_ptr<class GameObject>& obj);

public:
	shared_ptr<Shader>& GetShader() { return _shader; }

private:
	shared_ptr<Shader> _shader;

};

