#pragma once

class TimeManager;
class InputManager;
class SceneManager;
class RenderManager;
class GuiManager;
class ShaderManager;
class ResourceManager;

enum class MANAGER_TYPE
{
	Base = -1,
	Time,
	Input,
	Scene,
	Render,
	Gui,
	Shader,
	Resource,

	end
};

enum
{
	MANAGER_TYPE_COUNT = static_cast<int>(MANAGER_TYPE::end)
};

class Manager_Base
{
public:
	Manager_Base();
	virtual ~Manager_Base();

public:
	virtual void Init() {}
	virtual void Update() {}

};

template <typename C>
concept IsManagerType = requires(C c)
{
	derived_from<C, Manager_Base>;
};

template <typename C>
concept ManagerType = IsManagerType<C>;

class Manager
{
	DECLARE_SINGLE(Manager);

public:
	void Init();
	void Update();

public:

	template<ManagerType Ty>
	constexpr shared_ptr<Ty> GetManager()
	{
		int idx = (int)Ty::ty;
		return any_cast<shared_ptr<Ty>>(_managers[idx]);
	}


private:
	array<any, MANAGER_TYPE_COUNT> _managers;

	shared_ptr<TimeManager> _time;
	shared_ptr<InputManager> _input;
	shared_ptr<SceneManager> _scene;
	shared_ptr<RenderManager> _render;
	shared_ptr<GuiManager> _gui;
	shared_ptr<ShaderManager> _shader;
	shared_ptr<ResourceManager> _resource;
	
};