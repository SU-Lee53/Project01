#pragma once

class GameObject;
class Script;

class Scene
{
public:
	Scene();
	~Scene();

	void Init();
	void Update();
	void Render();

	void AddObject(shared_ptr<GameObject> obj);
	void RemoveObject(shared_ptr<GameObject> obj);

	void AddCamera(shared_ptr<GameObject> cam);
	void RemoveCamera(shared_ptr<GameObject> cam);
	[[nodiscard]] bool SetMainCamera(const string& name);

public:


private:
	unordered_set<shared_ptr<GameObject>> _objects;
	unordered_map<string, shared_ptr<GameObject>> _cameras;
	weak_ptr<GameObject> _currentCamera;

private:
	// Script for Scene
	vector<shared_ptr<Script>> _scripts;

};

