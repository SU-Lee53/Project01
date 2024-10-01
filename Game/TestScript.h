#pragma once
#include "Script.h"

class TestScript : public Script
{
public:
	virtual void Init() override;
	virtual void Update() override;

	void MouseToCenter();

private:
	friend class Test;

	bool _mouseOnOff = false;

	int _speed = 10.f;
	POINT _prevPoint;

	float _tempx = 0.f;
	float _tempy = 0.f;

	float _sensitivity = 10.f;

};

