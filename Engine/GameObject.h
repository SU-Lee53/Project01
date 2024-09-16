#pragma once
#include "Camera.h"
#include "transform.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

public:
	template <typename T,
	typename = typename enable_if<is_base_of_v<Component_Base, T>>::type>
	void AddComponent()
	{
		int idx = static_cast<int>(T::ty);
		_components[idx] = make_shared<T>();
	}

	template <typename T,
		typename = typename enable_if<is_base_of_v<Component_Base, T>>::type>
	shared_ptr<T> GetComponent()
	{
		int idx = static_cast<int>(T::ty);
		return static_pointer_cast<T>(_components[idx]);
	}

private:
	array<shared_ptr<Component_Base>, COMPONENT_COUNT> _components;

};
