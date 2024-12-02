#include "EnginePch.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Script.h"
//#include "CollisionHandler.h"

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
		cam->Init();
	}

	for (auto script : _scripts)
	{
		script->Init();
	}

	if (_globalLight)
		_globalLight->Init();

	//_collider->Init();
}

void Scene::Update()
{
	for (auto obj : _objects)
	{
		obj->Update();
	}

	_currentCamera.lock()->Update();

	for (auto script : _scripts)
	{
		script->Update();
	}

	if (_globalLight)
		_globalLight->Update();

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

void Scene::AddCamera(shared_ptr<GameObject> cam)
{
	_cameras.insert(cam);
}

bool Scene::RemoveCamera(const string& name)
{
	auto it = find_if(_cameras.begin(), _cameras.end(),
		[&name](decltype(*_cameras.begin()) p)->bool
		{
			return p->GetName() == name;
		}
	);

	if (it == _cameras.end())
	{
		return false;
	}

	_cameras.erase(it);
	return true;

}

bool Scene::SetMainCamera(const string& name)
{
	auto it = find_if(_cameras.begin(), _cameras.end(), 
		[&name](decltype(*_cameras.begin()) p)->bool
		{
			return p->GetName() == name;
		}
	);

	if (it != _cameras.end())
	{
		_currentCamera = *it;
		return true;
	}

	return false;
}

void Scene::AddScript(shared_ptr<Script<Scene>> script)
{
	script->SetOwner(shared_from_this());
	_scripts.push_back(script);
}

//void Scene::AddCollsionSet(shared_ptr<GameObject> obj1, shared_ptr<GameObject> obj2)
//{
//	if (obj1->GetComponent<Collider>() == nullptr
//		or obj2->GetComponent<Collider>() == nullptr)
//	{
//		assert(false);
//		return;
//	}
//	_collider->Add(obj1, obj2);
//}
//
//void Scene::RemoveCollsionSet(shared_ptr<GameObject> obj1, shared_ptr<GameObject> obj2)
//{
//	if (obj1->GetComponent<Collider>() == nullptr
//		or obj2->GetComponent<Collider>() == nullptr)
//	{
//		assert(false);
//		return;
//	}
//
//	_collider->Remove(obj1, obj2);
//}
