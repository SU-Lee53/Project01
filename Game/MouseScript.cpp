#include "pch.h"
#include "MouseScript.h"
#include "GameObject.h"

void MouseScript::Init()
{
	_prevPoint = { GAME.GetDesc().width, GAME.GetDesc().height };
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


	POINT point = INPUT->GetMousePos();
	Vec3 rot = GetOwner()->GetTransform()->GetRotation();

	if(_mouseOnOff)
	{
		if(INPUT->GetButton(KEY_TYPE::LBUTTON))
		{
			int32 diffx = _prevPoint.x - point.x;

			{
				_deltaX = (_prevPoint.x - point.x);	// Yaw
				_deltaY = (_prevPoint.y - point.y);	// Pitch

				rot.x -= _deltaY * _sensitivity * DELTA_TIME;
				rot.y -= _deltaX * _sensitivity * DELTA_TIME;

			}

			GetOwner()->GetTransform()->SetRotation(rot);
		}

	}
	else
	{
		ImGui::Begin("Non-mouse freelook");
		ImGui::SliderFloat("Pitch", &rot.x, -180.f, 180.f, "%.3f Deg");
		ImGui::SliderFloat("Yaw", &rot.y, -180.f, 180.f, "%.3f Deg");
		ImGui::End(); 

		GetOwner()->GetTransform()->SetRotation(rot);
	}


	{
		ImGui::Begin("Speeds");
		ImGui::SliderFloat("Cam Sensitivity", &_sensitivity, 0.f, 20.f);
		ImGui::SliderInt("Movement Speed", &_speed, 0.f, 20.f);
		ImGui::End();
	}


	_prevPoint = point;
}
