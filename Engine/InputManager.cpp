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
	UpdateKeyboard();
}

void InputManager::UpdateKeyboard()
{
	//array<BYTE, KEY_TYPE_COUNT> asciiKeys;
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciiKeys) == false)
		return;

	for (int key = 0; key < KEY_TYPE_COUNT; key++)
	{
		if (asciiKeys[key] & 0x80)
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
