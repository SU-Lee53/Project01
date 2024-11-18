#pragma once
#include "Component.h"
/*
	- New method
		- follow Component structure
		- Is it good? idk
*/

enum class COLLIDER_TYPE : uint8
{
	Base = 0,
	Sphere,
	Plane,
	AABB
};

class Collider : public Component<Collider>
{
public:
	Collider();
	virtual ~Collider();

public:
	void Init_impl()
	{
		InitCollider();
	}

	void Update_impl()
	{
		UpdateCollider();
	}

protected:
	virtual void InitCollider();
	virtual void UpdateCollider();

protected:
	function<void(Collider c)> _handler;
	Matrix transform;
};

// Collider Concept
template <typename C>
concept IsColliderType = requires (C c)
{
	derived_from<C, Collider>;
};

template <typename C>
concept ColliderType = IsColliderType<C>;
