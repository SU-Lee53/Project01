#include "EnginePch.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "GameObject.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Init()
{
}

void CollisionManager::Update()
{
	for (const auto s : _collisionSet)
	{
		 

	}
}

void CollisionManager::Add(shared_ptr<GameObject> key, shared_ptr<GameObject> value)
{
	_collisionSet.insert(make_pair(key, value));
}

void CollisionManager::Remove(shared_ptr<GameObject> key, shared_ptr<GameObject> value)
{
	auto it = find(_collisionSet.begin(), _collisionSet.end(), make_pair(key, value));
	_collisionSet.erase(it);
}
