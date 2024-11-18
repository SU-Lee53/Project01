#pragma once
#include "Collider.h"

class AABBCollider : public Collider
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
	const COLLIDER_TYPE _type = COLLIDER_TYPE::AABB;
};
