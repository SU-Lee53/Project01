#include "EnginePch.h"
#include "Manager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"

void Manager::Init()
{
	_time = make_shared<TimeManager>();
	_input = make_shared<InputManager>();
	_scene = make_shared<SceneManager>();

	_time->Init();
	_input->Init();
	// _scene->Init();
	
}

void Manager::Update()
{
	_time->Update();
	_input->Update();
	//_scene->Update();
}
