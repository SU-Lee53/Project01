#pragma once
#include "Component_Base.h"

enum class COMPONENT_TYPE
{
	Transform,
	Camera,
	MeshRenderer,

	End,

	ERROR_TYPE
};

enum
{
	COMPONENT_COUNT = static_cast<int>(COMPONENT_TYPE::End)
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
	virtual void Init_impl() {};
	virtual void Update_impl() {};

};

template<typename T>
inline Component<T>::Component()
{
}

template<typename T>
inline Component<T>::~Component()
{
}
