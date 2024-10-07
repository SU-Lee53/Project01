#pragma once
#include "Script.h"

class MouseScript : public Script
{
public:
	virtual void Init() override;
	virtual void Update() override;

private:
	friend class Test;

	bool _mouseOnOff = true;

	int _speed = 10.f;
	POINT _prevPoint;

	float _deltaX = 0.f;
	float _deltaY = 0.f;

	float _sensitivity = 10.f;

};

