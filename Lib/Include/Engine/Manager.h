#pragma once

class TimeManager;
class InputManager;
class SceneManager;

enum class ManagerType
{
	Base = -1,
	Time,
	Input,
	Scene,

	end
};

enum
{
	MANAGER_TYPE_COUNT = static_cast<int>(ManagerType::end)
};

class Manager
{
	DECLARE_SINGLE(Manager);

public:
	void Init();
	void Update();

public:
	template<ManagerType Type>
	constexpr auto GetManager()
	{
		if constexpr (Type == ManagerType::Time)
			return _time;
		else if constexpr (Type == ManagerType::Input)
			return _input;
		else if constexpr (Type == ManagerType::Scene)
			return _scene;
	}


private:
	shared_ptr<TimeManager> _time;
	shared_ptr<InputManager> _input;
	shared_ptr<SceneManager> _scene;

	
};