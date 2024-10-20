#include "EnginePch.h"
#include "SphereCollider.h"
#include "AABBCollider.h"
#include "PlaneCollider.h"
#include "Collision.h"

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
		return Collision::CheckCollision(shared_from_this(), dynamic_pointer_cast<AABBCollider>(other));
		
	case COLLIDER_TYPE::Plane:
		return Collision::CheckCollision(shared_from_this(), dynamic_pointer_cast<PlaneCollider>(other));

	case COLLIDER_TYPE::Sphere:
		return Collision::CheckCollision(shared_from_this(), dynamic_pointer_cast<SphereCollider>(other));

	default:
		assert(false);
	}
}
