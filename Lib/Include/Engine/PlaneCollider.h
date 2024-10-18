#pragma once
#include "Collider.h"

class PlaneCollider : public Collider, public enable_shared_from_this<PlaneCollider>
{
public:
	PlaneCollider();
	virtual ~PlaneCollider();

public:
	template<ColliderType T>
	bool CheckCollision(shared_ptr<T> other);

	friend class Collision;

private:
	float _distanceFromOrigin;
	Vec3 _normal;

public:
	using _colliderType = PlaneCollider;
};

template<ColliderType T>
inline bool PlaneCollider::CheckCollision(shared_ptr<T> other)
{
	return Collision::CheckCollision(shared_from_this(), other);
}