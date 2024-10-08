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
	_objects.insert(obj);
}

void Scene::RemoveObject(shared_ptr<GameObject> obj)
{
	_objects.erase(obj);
}

void Scene::AddCamera(const string& name, shared_ptr<GameObject> cam)
{
	_cameras.insert(make_pair(name, cam));
}

void Scene::RemoveCamera(const string& name)
{
	auto it = find_if(_cameras.begin(), _cameras.end(),
		[&name](decltype(*_cameras.begin()) p)->bool
		{
			return p.first == name;
		}
	);

	if (it != _cameras.end())
	{
		assert(false);
	}

	_cameras.erase(it);

}

bool Scene::SetMainCamera(const string& name)
{
	auto it = find_if(_cameras.begin(), _cameras.end(), 
		[&name](decltype(*_cameras.begin()) p)->bool
		{
			return p.first == name;
		}
	);

	if (it != _cameras.end())
	{
		_currentCamera = it->second;
		return true;
	}

	return false;
}

void Scene::AddScript(shared_ptr<Script<Scene>> script)
{
	_scripts.push_back(script);
}
