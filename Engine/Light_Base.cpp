#include "EnginePch.h"
#include "Light_Base.h"
#include "GlobalLight.h"
// #include "SpotLight.h"

Light_Base::Light_Base()
{
}

Light_Base::~Light_Base()
{
}

void Light_Base::Update_impl()
{
	if (ty == COMPONENT_TYPE::GlobalLight)
		(static_cast<GlobalLight*>(this))->Update_impl();
	//if(ty == COMPONENT_TYPE::SpotLight)
	//	(static_cast<SpotLight*>(this))->Update_impl();
	else
		assert(false);
}
