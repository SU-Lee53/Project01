#pragma once

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
	void Add(shared_ptr<Collider> key, shared_ptr<Collider> value);
	void Remove(shared_ptr<Collider> key, shared_ptr<Collider> value);

private:
	unordered_map<shared_ptr<Collider>, shared_ptr<Collider>> _collisionSet;

};

