#pragma once
#include "Manager.h"
#include "Collider_Base.h"

/*
	CollisionManager wasn't mean to work like manager
	BUT, I guess this is more appropriate way
*/

class CollisionManager : public Manager_Base
{
public:
	CollisionManager();
	virtual ~CollisionManager();

public:
	virtual void Init();
	virtual void Update();

public:
	void Add(shared_ptr<Collider_Base> key, shared_ptr<Collider_Base> value);
	void Remove(shared_ptr<Collider_Base> key, shared_ptr<Collider_Base> value);

private:
	unordered_map<shared_ptr<Collider_Base>, shared_ptr<Collider_Base>> _collisionSet;

};

