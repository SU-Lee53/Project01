#pragma once

class Shader;
class Mesh;
class GameObject;

class RenderManager
{
public:
	RenderManager();
	~RenderManager();

public:
	void Init(shared_ptr<Shader> shader) { _shader = shader; };
	void Update();
	void Render();

public:
	void PushToRenderQueue(shared_ptr<GameObject> obj) { _renderObj.push_back(obj); }

public:
	shared_ptr<Shader>& GetShader() { return _shader; }

private:
	shared_ptr<Shader> _shader;
	vector<shared_ptr<GameObject>> _renderObj;
};

