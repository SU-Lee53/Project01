#pragma once
#include "Collider_Base.h"

class PlaneCollider : public Collider_Base, public enable_shared_from_this<PlaneCollider>
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
};

template<ColliderType T>
inline bool PlaneCollider::CheckCollision(shared_ptr<T> other)
{
	return Collision::CheckCollision(shared_from_this(), other);
}