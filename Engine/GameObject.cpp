#include "EnginePch.h"
#include "GameObject.h"

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
		component->Init();
	}
}

void GameObject::Update()
{
	for (const auto& component : _components)
	{
		component->Update();
	}
}
