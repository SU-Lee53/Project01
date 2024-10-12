#pragma once
#include "Script.h"

class MouseScript : public Script<GameObject>
{
public:
	virtual void Init() override;
	virtual void Update() override;

private:
	friend class Test;

	bool _mouseOnOff = true;

	int _speed = 10.f;
	POINT _point;

	float _deltaX = 0.f;
	float _deltaY = 0.f;

	float _sensitivity = 0.1f;

};

