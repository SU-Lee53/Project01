#pragma once

class GameObject;
class Collider;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

public:
	void Init();
	void Update();

public:
	void Add(shared_ptr<GameObject> key, shared_ptr<GameObject> value);
	void Remove(shared_ptr<GameObject> key, shared_ptr<GameObject> value);

private:
	unordered_map<shared_ptr<GameObject>, shared_ptr<GameObject>> _collisionSet;

};

