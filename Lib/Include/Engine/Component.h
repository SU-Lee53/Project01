#pragma once
#include "Component_Base.h"

enum class COMPONENT_TYPE
{
	Transform,							// 0
	Camera,								// 1
	MeshRenderer,						// 2

	Light_Base,							// 3
	GlobalLight = Light_Base,
	SpotLight = GlobalLight,

	//Collider,
	//AABBColider = Collider,						// 4
	//SphereColider = AABBColider,
	//PlaneColider = SphereColider,
	
	/*
		- TODO : Add Below
		Light,
		Gravity,
		Collider
	*/

	Script,

	End,
};

enum
{
	COMPONENT_COUNT = static_cast<int>(COMPONENT_TYPE::End) - 1
};

template <typename T>
class Component : public Component_Base
{
public:
	Component();
	virtual ~Component();

public:
	virtual void Init() override
	{
		(static_cast<T*>(this))->Init_impl();
	}
	virtual void Update() override
	{
		(static_cast<T*>(this))->Update_impl();
	}

protected:
	void Init_impl() {};
	void Update_impl() {};

};

template<typename T>
inline Component<T>::Component()
{
}

template<typename T>
inline Component<T>::~Component()
{
}
