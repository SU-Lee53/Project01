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
	function<void(shared_ptr<Collider>)> _handler;

private:
	Vec3 _position;
	Matrix _srt;

private:
	unordered_set<shared_ptr<Collider>> _collisionMap;

public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::Collider;
	COLLIDER_TYPE _colliderType;
};

template <typename C>
concept IsColliderType = requires(C c)
{
	std::derived_from<C, Collider>;
};

template <typename C>
concept ColliderType = IsColliderType<C>;
