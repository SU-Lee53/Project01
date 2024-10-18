#include "EnginePch.h"
#include "CollisionManager.h"
#include "Collider.h"

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
		s.first->
	}
}

void CollisionManager::Add(shared_ptr<Collider> key, shared_ptr<Collider> value)
{
	_collisionSet.insert(make_pair(key, value));
}

void CollisionManager::Remove(shared_ptr<Collider> key, shared_ptr<Collider> value)
{
	auto it = find(_collisionSet.begin(), _collisionSet.end(), make_pair(key, value));
	_collisionSet.erase(it);
}
