#include "pch.h"
#include "MouseScript.h"
#include "GameObject.h"

void MouseScript::Init()
{
}

void MouseScript::Update()
{

	Vec3 pos = GetOwner()->GetTransform()->GetPosition();

	if (INPUT->GetButton(KEY_TYPE::W))
	{
		pos += GetOwner()->GetTransform()->GetLook() * _speed * DELTA_TIME;
	}
	if (INPUT->GetButton(KEY_TYPE::A))
	{
		pos -= GetOwner()->GetTransform()->GetRight() * _speed * DELTA_TIME;
	}
	if (INPUT->GetButton(KEY_TYPE::S))
	{
		pos -= GetOwner()->GetTransform()->GetLook() * _speed * DELTA_TIME;
	}
	if (INPUT->GetButton(KEY_TYPE::D))
	{
		pos += GetOwner()->GetTransform()->GetRight() * _speed * DELTA_TIME;
	}
	if (INPUT->GetButton(KEY_TYPE::SPACE))
	{
		pos += GetOwner()->GetTransform()->GetUp() * _speed * DELTA_TIME;
	}
	if (INPUT->GetButton(KEY_TYPE::CTRL))
	{
		pos -= GetOwner()->GetTransform()->GetUp() * _speed * DELTA_TIME;
	}

	GetOwner()->GetTransform()->SetPosition(pos);



	if (INPUT->GetButtonDown(KEY_TYPE::E))
	{
		if (_mouseOnOff)
			_mouseOnOff = false;
		else
			_mouseOnOff = true;
	}

	GetCursorPos(&_point);
	Vec3 rot = GetOwner()->GetTransform()->GetRotation();

	// Update Center
	RECT rMyRect;
	GetClientRect(GAME.GetDesc().hWnd, (LPRECT)&rMyRect);
	ClientToScreen(GAME.GetDesc().hWnd, (LPPOINT)&rMyRect.left);
	ClientToScreen(GAME.GetDesc().hWnd, (LPPOINT)&rMyRect.right);

	int screenCenterX = 0, screenCenterY = 0;
	screenCenterX = rMyRect.left + GAME.GetDesc().width / 2;
	screenCenterY = rMyRect.top + GAME.GetDesc().height / 2;

	if(_mouseOnOff)
	{
		{
			_deltaX = (_point.x - screenCenterX);	// Yaw
			_deltaY = (_point.y - screenCenterY);	// Pitch

			rot.x += _deltaY * _sensitivity;
			rot.y += _deltaX * _sensitivity;
		}

		GetOwner()->GetTransform()->SetRotation(rot);

		SetCursorPos(screenCenterX, screenCenterY);

	}
	else
	{
		if (ImGui::Begin("Non-mouse freelook"))
		{
			ImGui::SliderFloat("Pitch", &rot.x, -180.f, 180.f, "%.3f Deg");
			ImGui::SliderFloat("Yaw", &rot.y, -180.f, 180.f, "%.3f Deg");

			GetOwner()->GetTransform()->SetRotation(rot);

			ImGui::SliderFloat("Cam Sensitivity", &_sensitivity, 0.f, 20.f);
			ImGui::SliderInt("Movement Speed", &_speed, 0.f, 20.f);
			ImGui::End();
		}
	}
}
