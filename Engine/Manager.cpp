#include "EnginePch.h"
#include "Manager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "GuiManager.h"
#include "ShaderManager.h"

void Manager::Init()
{
	_managers[(int)MANAGER_TYPE::Time] = make_shared<TimeManager>();
	_managers[(int)MANAGER_TYPE::Input] = make_shared<InputManager>();
	_managers[(int)MANAGER_TYPE::Scene] = make_shared<SceneManager>();
	_managers[(int)MANAGER_TYPE::Render] = make_shared<RenderManager>();
	_managers[(int)MANAGER_TYPE::Gui] = make_shared<GuiManager>();
	_managers[(int)MANAGER_TYPE::Shader] = make_shared<ShaderManager>();

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


//////////////////////////////////////////////


Manager_Base::Manager_Base()
{
}

Manager_Base::~Manager_Base()
{
}
