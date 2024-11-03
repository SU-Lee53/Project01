#pragma once
#include "Script.h"

class Light;

class LightScript : public Script<GameObject>
{
public:
	virtual void Init() override;
	virtual void Update() override;

private:
	GlobalLightData _lightData;
	float _dragSpeed = 0.1f;

};

