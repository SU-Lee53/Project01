#include "EnginePch.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	_currentScene = make_shared<Scene>();

	// May be change in future
	_scenes.insert(make_pair("main", _currentScene));
}

void SceneManager::Update()
{
	_currentScene->Update();
}

void SceneManager::AddScene(const string& name, shared_ptr<Scene> scene)
{
	_scenes.insert(make_pair(name, scene));
}

shared_ptr<Scene> SceneManager::GetScene(const string& name)
{
	return _scenes[name];
}

shared_ptr<Scene> SceneManager::GetCurrentScene()
{
	return _currentScene;
}
