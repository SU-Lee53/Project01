#include "EnginePch.h"
#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Init()
{
	_states.resize(KEY_TYPE_COUNT, KEY_STATE::NONE);
}

void InputManager::Update()
{
}

void InputManager::UpdateKeyboard()
{
	array<BYTE, KEY_TYPE_COUNT> keys;
	if (::GetKeyboardState(keys.data()) == false)
		return;

	for (auto& key : keys)
	{
		if (key & 0x80)
		{
			KEY_STATE& state = _states[key];

			if (state == KEY_STATE::PRESS or state == KEY_STATE::DOWN)
				state = KEY_STATE::PRESS;
			else
				state = KEY_STATE::DOWN;
		}
		else
		{
			KEY_STATE& state = _states[key];

			if (state == KEY_STATE::PRESS or state == KEY_STATE::DOWN)
				state = KEY_STATE::UP;
			else
				state = KEY_STATE::NONE;
		}
	}
}

void InputManager::UpdateMouse()
{
}
