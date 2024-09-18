#include "EnginePch.h"
#include "GameObject.h"
#include "Transform.h"

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
		if(component)
			component->Init();
	}
}

void GameObject::Update()
{
	for (const auto& component : _components)
	{
		if (component)
			component->Update();
	}
}
