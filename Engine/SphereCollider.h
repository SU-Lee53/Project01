#pragma once
#include "Collider.h"
#include "Collision.h"


class SphereCollider : public Collider, public enable_shared_from_this<SphereCollider>
{
public:
	SphereCollider();
	virtual ~SphereCollider();

public:
	bool CheckCollision(shared_ptr<Collider> other);

	friend class Collision;

private:
	Vec3 _center;
	float _radius;

};
