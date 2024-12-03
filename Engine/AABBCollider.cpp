#include "EnginePch.h"
#include "AABBCollider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "GameObject.h"

AABBCollider::AABBCollider()
	:BaseCollider(COLLIDER_TYPE::AABB)
{
}

AABBCollider::~AABBCollider()
{
}

void AABBCollider::UpdateCollider()
{
	_boundingBox.Center = GetOwner()->GetTransform()->GetPosition();
}

bool AABBCollider::CheckCollision(shared_ptr<BaseCollider> other)
{
	COLLIDER_TYPE type = other->GetColliderType();

	switch (type)
	{
	case COLLIDER_TYPE::Sphere:
		return _boundingBox.Intersects(dynamic_pointer_cast<SphereCollider>(other)->GetBoundingSphere());
	case COLLIDER_TYPE::AABB:
		return _boundingBox.Intersects(dynamic_pointer_cast<AABBCollider>(other)->GetBoundingBox());
	case COLLIDER_TYPE::Plane:
		return CheckIntersectWithPlane(dynamic_pointer_cast<PlaneCollider>(other)->GetBoundingPlane());
	}

	return false;
}

bool AABBCollider::CheckIntersectWithPlane(const BoundingPlane& p)
{
    float pLen = _boundingBox.Extents.x * fabsf(p.Normal.x) +
        _boundingBox.Extents.y * fabsf(p.Normal.y) +
        _boundingBox.Extents.z * fabsf(p.Normal.z);

    float dot = p.Normal.Dot(_boundingBox.Center);
    float dist = dot - p.Distance;

    return fabsf(dist) <= pLen;
}
