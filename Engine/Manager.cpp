#include "EnginePch.h"
#include "Manager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "GuiManager.h"
#include "ShaderManager.h"
#include "ResourceManager.h"

void Manager::Init()
{
	_managers[(int)MANAGER_TYPE::Time] = make_shared<TimeManager>();
	_managers[(int)MANAGER_TYPE::Input] = make_shared<InputManager>();
	_managers[(int)MANAGER_TYPE::Scene] = make_shared<SceneManager>();
	_managers[(int)MANAGER_TYPE::Shader] = make_shared<ShaderManager>();
	_managers[(int)MANAGER_TYPE::Render] = make_shared<RenderManager>();
	_managers[(int)MANAGER_TYPE::Gui] = make_shared<GuiManager>();
	_managers[(int)MANAGER_TYPE::Resource] = make_shared<ResourceManager>();

	GUI->Init();
	TIME->Init();
	INPUT->Init();
	SHADER->Init();
	RENDER->Init();
	RESOURCE->Init();
	SCENE->Init();
}

void Manager::Update()
{
	GUI->Update();
	TIME->Update();
	INPUT->Update();
	SHADER->Update();
	RENDER->Update();
	RESOURCE->Update();
	SCENE->Update();
}


//////////////////////////////////////////////


Manager_Base::Manager_Base()
{
}

Manager_Base::~Manager_Base()
{
}
