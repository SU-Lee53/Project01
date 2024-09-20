#pragma once

#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "GuiManager.h"

enum class MANAGER_TYPE
{
	Base = -1,
	Time,
	Input,
	Scene,
	Render,
	Gui,

	end
};

enum
{
	MANAGER_TYPE_COUNT = static_cast<int>(MANAGER_TYPE::end)
};

class Manager
{
	DECLARE_SINGLE(Manager);

public:
	void Init(shared_ptr<Shader> shader);
	void Update();

public:

	template<MANAGER_TYPE Type>
	constexpr auto GetManager()
	{
		if constexpr (Type == MANAGER_TYPE::Time)
			return _time;
		else if constexpr (Type == MANAGER_TYPE::Input)
			return _input;
		else if constexpr (Type == MANAGER_TYPE::Scene)
			return _scene;
		else if constexpr (Type == MANAGER_TYPE::Render)
			return _render;
		else if constexpr (Type == MANAGER_TYPE::Gui)
			return _gui;
	}


private:
	shared_ptr<TimeManager> _time;
	shared_ptr<InputManager> _input;
	shared_ptr<SceneManager> _scene;
	shared_ptr<RenderManager> _render;
	shared_ptr<GuiManager> _gui;
	
};