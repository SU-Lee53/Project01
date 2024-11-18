#include "EnginePch.h"
#include "CollisionHandler.h"
#include "Collider.h"
#include "GameObject.h"

CollisionHandler::CollisionHandler()
{
}

CollisionHandler::~CollisionHandler()
{
}

void CollisionHandler::Init()
{
}

void CollisionHandler::Update()
{
	for (const auto s : _possibleCollisionMap)
	{
		 

	}
}

void CollisionHandler::Add(shared_ptr<GameObject> key, shared_ptr<GameObject> value)
{
	_possibleCollisionMap.insert(make_pair(key, value));
}

void CollisionHandler::Remove(shared_ptr<GameObject> key, shared_ptr<GameObject> value)
{
	auto it = find(_possibleCollisionMap.begin(), _possibleCollisionMap.end(), make_pair(key, value));
	_possibleCollisionMap.erase(it);
}
