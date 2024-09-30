#include "EnginePch.h"
#include "GameObject.h"
#include "Transform.h"
#include "Script.h"

GameObject::GameObject()
{
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
}

void GameObject::AddScript(shared_ptr<Script> script)
{
	script->SetOwner(shared_from_this());
	_scripts.push_back(script);
}
