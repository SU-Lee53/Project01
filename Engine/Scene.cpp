#include "EnginePch.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Init()
{
	for (auto obj : _objects)
	{
		obj->Init();
	}
}

void Scene::Update()
{
	for (auto obj : _objects)
	{
		obj->Update();
	}
}

void Scene::Render()
{

}
