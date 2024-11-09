#pragma once
#include "Collider.h"

class AABBCollider : public Collider, public enable_shared_from_this<AABBCollider>
{
public:
	AABBCollider();
	virtual ~AABBCollider();

public:
	bool CheckCollision(shared_ptr<Collider> other);

	friend class Collision;

private:
	float _center;
	Vec3 _size;

public:
	constexpr static COLLIDER_TYPE _colliderType = COLLIDER_TYPE::AABB;
};
