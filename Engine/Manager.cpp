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
	
}

void Manager::Update()
{
}
