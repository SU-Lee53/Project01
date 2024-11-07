#pragma once
#include "Manager.h"

class Scene;

class SceneManager : public Manager_Base
{
public:
	SceneManager();
	virtual ~SceneManager();

public:
	virtual void Init() override;
	virtual void Update() override;


public:
	void AddScene(const string& name, shared_ptr<Scene> scene);

public:
	shared_ptr<Scene> GetScene(const string& name);
	shared_ptr<Scene> GetCurrentScene();
	
private:
	shared_ptr<Scene> _currentScene;
	unordered_map<string, shared_ptr<Scene>> _scenes;


public:
	constexpr static  MANAGER_TYPE ty = MANAGER_TYPE::Scene;
};

