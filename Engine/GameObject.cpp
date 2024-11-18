#include "EnginePch.h"
#include "GameObject.h"
#include "Transform.h"
#include "Script.h"
#include "SphereCollider.h"
#include "AABBCollider.h"
#include "PlaneCollider.h"

GameObject::GameObject()
{
	for (auto& c : _components)
	{
		c = nullptr;
	}

	_collider = nullptr;
}

GameObject::~GameObject()
{

}

void GameObject::Init()
{
	for (const auto& component : _components)
	{
		if (component)
			component->Init();
	}

	for (const auto& script : _scripts)
	{
		script->Init();
	}

	if(_collider)
		_collider->Init();
}

void GameObject::Update()
{
	for (const auto& component : _components)
	{ 
		if (component)
			component->Update();
	}

	for (const auto& script : _scripts)
	{
		script->Update();
	}

	if (_collider)
		_collider->Update();
}

void GameObject::AddScript(shared_ptr<Script<GameObject>> script)
{
	script->SetOwner(shared_from_this());
	_scripts.push_back(script);
}
