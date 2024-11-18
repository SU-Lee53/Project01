#pragma once

class GameObject;
//class CollisionHandler;

class Scene : public enable_shared_from_this<Scene>
{
public:
	Scene();
	~Scene();

	void Init();
	void Update();
	void Render();

	void AddObject(shared_ptr<GameObject> obj);
	void RemoveObject(shared_ptr<GameObject> obj);
	unordered_set<shared_ptr<GameObject>> GetObjects() { return _objects; }


	void AddCamera(const string& name, shared_ptr<GameObject> cam);
	void RemoveCamera(const string& name);
	bool SetMainCamera(const string& name);
	unordered_map<string, shared_ptr<GameObject>> GetCameras() { return _cameras; }

	void AddScript(shared_ptr<Script<Scene>> script);

public:
	//void AddCollsionSet(shared_ptr<GameObject> obj1, shared_ptr<GameObject> obj2);
	//void RemoveCollsionSet(shared_ptr<GameObject> obj1, shared_ptr<GameObject> obj2);

private:
	unordered_set<shared_ptr<GameObject>> _objects;
	unordered_map<string, shared_ptr<GameObject>> _cameras;
	weak_ptr<GameObject> _currentCamera;

private:
	//Script for Scene
	vector<shared_ptr<Script<Scene>>> _scripts;
	//shared_ptr<CollisionHandler> _collider;
};

