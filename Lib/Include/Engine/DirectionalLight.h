#pragma once
#include "Light_Base.h"

class DirectionalLight : public Light_Base
{
public:
	DirectionalLight();
	virtual ~DirectionalLight();

private:



public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::DirectionalLight;
};

