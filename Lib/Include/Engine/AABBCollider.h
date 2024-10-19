#pragma once
#include "Collider.h"

class AABBCollider : public Collider, public enable_shared_from_this<AABBCollider>
{
public:
	AABBCollider();
	virtual ~AABBCollider();

public:
	template<ColliderType T>
	bool CheckCollision(shared_ptr<T> other);

	friend class Collision;

private:
	float _center;
	Vec3 _size;
};

template<ColliderType T>
inline bool AABBCollider::CheckCollision(shared_ptr<T> other)
{
	return Collision::CheckCollision(shared_from_this(), other);
}
