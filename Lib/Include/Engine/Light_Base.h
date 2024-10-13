#pragma once
#include "Component.h"

class Light_Base : public Component<Light_Base>
{
public:
	Light_Base();
	virtual ~Light_Base();

private:

public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::Light_Base;
};

