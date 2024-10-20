#pragma once
#include "Collider.h"

class PlaneCollider : public Collider, public enable_shared_from_this<PlaneCollider>
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
};
