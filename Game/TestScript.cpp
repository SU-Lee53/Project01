#include "pch.h"
#include "TestScript.h"
#include "GameObject.h"

void TestScript::Init()
{
	_prevPoint = { GAME.GetDesc().width, GAME.GetDesc().height };
}

void TestScript::Update()
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

		int32 diffx = _prevPoint.x - point.x;

		{
			_tempx = (_prevPoint.x - point.x) * DELTA_TIME;	// Yaw
			_tempy = (_prevPoint.y - point.y) * DELTA_TIME;	// Pitch

			rot.x -= _tempy * _sensitivity;
			rot.y -= _tempx * _sensitivity;

		}

		MouseToCenter();

	}
	else
	{
		ImGui::Begin("Test on Testscript");
		ImGui::SliderFloat("Pitch", &rot.x, -180.f, 180.f);
		ImGui::SliderFloat("Yaw", &rot.y, -180.f, 180.f);
		ImGui::End();
	}

	GetOwner()->GetTransform()->SetRotation(rot);


	_prevPoint = point;

}

void TestScript::MouseToCenter()
{
	//RECT rect;
	SetCursorPos(GAME.GetDesc().width / 2, GAME.GetDesc().height / 2);
	_prevPoint = POINT{ GAME.GetDesc().width / 2, GAME.GetDesc().height / 2 };
	_tempx = 0.f;
	_tempy = 0.f;

	//GetClientRect(GAME.GetDesc().hWnd, &rect);
	//
	//POINT ul;	// upper-left
	//ul.x = rect.left;
	//ul.y = rect.top;
	//
	//POINT lr;	// lower-right
	//lr.x = rect.right;
	//lr.y = rect.bottom;
	//
	//MapWindowPoints(GAME.GetDesc().hWnd, nullptr, &ul, 1);
	//MapWindowPoints(GAME.GetDesc().hWnd, nullptr, &lr, 1);
	//
	//rect.left = ul.x;
	//rect.top = ul.y;
	//rect.right = lr.x;
	//rect.bottom = lr.y;
	//
	//ClipCursor(&rect);
}