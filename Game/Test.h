#pragma once
#include "Execute.h"

class TestScript;

class Test : public Execute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<GameObject> _obj;
	shared_ptr<GameObject> _cam;
	float temp = 0.f;

	shared_ptr<Script<GameObject>> _script;
};

