#pragma once
#include "Component.h"

enum COLLIDER_TYPE
{
	Base = -1,
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
	void Update_impl();

public:

private:
	Vec3 _position;
	Matrix _srt;

public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::Collider;
	using _colliderType = Collider;
};


template <typename C>
concept IsColliderType = requires(C c)
{
	derived_from<C, Collider>;
};

template <typename C>
concept ColliderType = IsColliderType<C>;
