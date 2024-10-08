#include "EnginePch.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Script.h"

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

	for (auto script : _scripts)
	{
		script->Init();
	}
}

void Scene::Update()
{
	for (auto obj : _objects)
	{
		obj->Update();
	}

	for (auto script : _scripts)
	{
		script->Update();
	}
}

void Scene::Render()
{

}

void Scene::AddObject(shared_ptr<GameObject> obj)
{
}

void Scene::RemoveObject(shared_ptr<GameObject> obj)
{
}

void Scene::AddCamera(shared_ptr<GameObject> cam)
{
}

void Scene::RemoveCamera(shared_ptr<GameObject> cam)
{
}

bool Scene::SetMainCamera(const string& name)
{
	auto it = find(_cameras.begin(), _cameras.end(), name);
	if (it != _cameras.end())
	{
		_currentCamera = it->second;
		return true;
	}

	return false;
}
