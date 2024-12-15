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
	unordered_set<shared_ptr<GameObject>>& GetObjects() { return _objects; }

	void AddCamera(shared_ptr<GameObject> cam);
	bool RemoveCamera(const string& name);
	bool SetMainCamera(const string& name);

	unordered_set<shared_ptr<GameObject>>& GetCameras() { return _cameras; }
	shared_ptr<GameObject> GetMainCamera() { return _currentCamera.lock(); }

	void AddScript(shared_ptr<Script<Scene>> script);

	void SetGlobalLight(shared_ptr<GameObject> light) { _globalLight = light; };
	shared_ptr<GameObject> GetGlobalLight() { return _globalLight; }

public:
	void AddCollisionSet(pair<shared_ptr<BaseCollider>, shared_ptr<BaseCollider>> pair);
	void RemoveCollisionSet(pair<shared_ptr<BaseCollider>, shared_ptr<BaseCollider>> pair);
	void CheckCollision();

	set<pair<shared_ptr<BaseCollider>, shared_ptr<BaseCollider>>> GetPossibleCollisionPairs() { return _possibleCollisionPairs; }
	set<pair<shared_ptr<BaseCollider>, shared_ptr<BaseCollider>>> GetCollidedPairs() { return _collidedPairs; }

private:
	unordered_set<shared_ptr<GameObject>> _objects;
	unordered_set<shared_ptr<GameObject>> _cameras;
	weak_ptr<GameObject> _currentCamera;
	shared_ptr<GameObject> _globalLight;

private:
	//Script for Scene
	vector<shared_ptr<Script<Scene>>> _scripts;

private:
	set<pair<shared_ptr<BaseCollider>, shared_ptr<BaseCollider>>> _possibleCollisionPairs;
	set<pair<shared_ptr<BaseCollider>, shared_ptr<BaseCollider>>> _collidedPairs;


};

