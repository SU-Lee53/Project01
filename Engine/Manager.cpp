#include "EnginePch.h"
#include "Manager.h"

void Manager::Init()
{
	_time = make_shared<TimeManager>();
	_input = make_shared<InputManager>();
	_scene = make_shared<SceneManager>();
	_render = make_shared<RenderManager>();
	_gui = make_shared<GuiManager>();
	_shader = make_shared<ShaderManager>();

	_time->Init();
	_input->Init();
	// _scene->Init();
	_render->Init();
	_gui->Init();
	_shader->Init();
}

void Manager::Update()
{
	_time->Update();
	_input->Update();
	//_scene->Update();
	_render->Update();
	_gui->Update();
	//_shader->Update();
}
