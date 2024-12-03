#include "EnginePch.h"
#include "SphereCollider.h"
#include "AABBCollider.h"
#include "PlaneCollider.h"
#include "GameObject.h"

SphereCollider::SphereCollider()
	:BaseCollider(COLLIDER_TYPE::Sphere)
{
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::UpdateCollider()
{
	_boundingSphere.Center = GetOwner()->GetTransform()->GetPosition();
	Vec3 scale = GetOwner()->GetTransform()->GetScale();
	_boundingSphere.Radius = _radius * max(max(scale.x, scale.y), scale.z);
}

bool SphereCollider::CheckCollision(shared_ptr<BaseCollider> other)
{
	COLLIDER_TYPE type = other->GetColliderType();

	switch (type)
	{
	case COLLIDER_TYPE::Sphere:
		return _boundingSphere.Intersects(dynamic_pointer_cast<SphereCollider>(other)->GetBoundingSphere());
	case COLLIDER_TYPE::AABB:
		return _boundingSphere.Intersects(dynamic_pointer_cast<AABBCollider>(other)->GetBoundingBox());
	case COLLIDER_TYPE::Plane:
		return CheckIntersectWithPlane(dynamic_pointer_cast<PlaneCollider>(other)->GetBoundingPlane());
	}

	return false;
}

bool SphereCollider::CheckIntersectWithPlane(const BoundingPlane& p)
{
	Vec3 closestPoint = BoundingPlane::ClosestPoint(p, _boundingSphere.Center);
	float distSq = (_boundingSphere.Center - closestPoint).LengthSquared();
	float radiusSq = pow(_boundingSphere.Radius, 2);
	return distSq <= radiusSq;

	return false;
}
