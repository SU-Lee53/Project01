#include "EnginePch.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Script.h"
#include "CollisionHandler.h"

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

	for (auto cam : _cameras)
	{
		cam.second->Init();
	}

	for (auto script : _scripts)
	{
		script->Init();
	}

	_collider->Init();
}

void Scene::Update()
{
	for (auto obj : _objects)
	{
		obj->Update();
	}

	for (auto cam : _cameras)
	{
		cam.second->Update();
	}

	for (auto script : _scripts)
	{
		script->Update();
	}
}

void Scene::Render()
{
	RENDER->Render();
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

void Scene::AddCollsionSet(shared_ptr<GameObject> obj1, shared_ptr<GameObject> obj2)
{
	if (obj1->GetComponent<Collider>() == nullptr
		or obj2->GetComponent<Collider>() == nullptr)
	{
		assert(false);
		return;
	}
	_collider->Add(obj1, obj2);
}

void Scene::RemoveCollsionSet(shared_ptr<GameObject> obj1, shared_ptr<GameObject> obj2)
{
	if (obj1->GetComponent<Collider>() == nullptr
		or obj2->GetComponent<Collider>() == nullptr)
	{
		assert(false);
		return;
	}

	_collider->Remove(obj1, obj2);
}
