#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider();
	virtual ~SphereCollider();

public:
	void ShrinkToFit();

public:
	bool CheckCollision(shared_ptr<Collider> other);

	friend class Collision;

private:
	Vec3 _center;
	float _radius;

public:
	const COLLIDER_TYPE _type = COLLIDER_TYPE::Sphere;
};
