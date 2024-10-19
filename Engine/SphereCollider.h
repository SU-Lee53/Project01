#pragma once
#include "Collider.h"
#include "Collision.h"


class SphereCollider : public Collider, public enable_shared_from_this<SphereCollider>
{
public:
	SphereCollider();
	virtual ~SphereCollider();

public:
	template<ColliderType T>
	bool CheckCollision(shared_ptr<T> other);

	friend class Collision;

private:
	Vec3 _center;
	float _radius;
};

template<ColliderType T>
inline bool SphereCollider::CheckCollision(shared_ptr<T> other)
{
	return Collision::CheckCollision(shared_from_this(), other);
}
