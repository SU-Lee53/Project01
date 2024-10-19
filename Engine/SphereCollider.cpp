#include "EnginePch.h"
#include "SphereCollider.h"

SphereCollider::SphereCollider()
{
	_colliderType = COLLIDER_TYPE::Sphere;
}

SphereCollider::~SphereCollider()
{
}

bool SphereCollider::CheckCollision(shared_ptr<Collider> other)
{
	auto type = other->_colliderType;

	switch (type)
	{
	case COLLIDER_TYPE::AABB:
		Collision::CheckCollision(shared_from_this(), dynamic_pointer_cast<AABBCollider>(other));
	case COLLIDER_TYPE::Plane:

	case COLLIDER_TYPE::Sphere:

	default:
		assert(false);
	}
}
