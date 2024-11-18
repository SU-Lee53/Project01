#pragma once
#include "Collider.h"

class PlaneCollider : public Collider
{
public:
	PlaneCollider();
	virtual ~PlaneCollider();

public:
	bool CheckCollision(shared_ptr<Collider> other);

	friend class Collision;

private:
	float _distanceFromOrigin;
	Vec3 _normal;

public:
	const COLLIDER_TYPE _type = COLLIDER_TYPE::Plane;
};
