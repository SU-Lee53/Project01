#include "EnginePch.h"
#include "Manager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"

void Manager::Init(shared_ptr<Shader> shader)
{
	_time = make_shared<TimeManager>();
	_input = make_shared<InputManager>();
	_scene = make_shared<SceneManager>();
	_render = make_shared<RenderManager>();

	_time->Init();
	_input->Init();
	// _scene->Init();
	_render->Init(shader);
}

void Manager::Update()
{
	_time->Update();
	_input->Update();
	//_scene->Update();
	_render->Update();
}
