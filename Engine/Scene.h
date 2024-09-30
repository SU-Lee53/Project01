#pragma once

class GameObject;

class Scene
{
public:
	Scene();
	~Scene();

	void Init();
	void Update();
	void Render();

private:
	unordered_set<shared_ptr<GameObject>> _objects;
	unordered_set<shared_ptr<GameObject>> _cameras;

};

