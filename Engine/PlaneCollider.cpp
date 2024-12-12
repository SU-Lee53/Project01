#include "EnginePch.h"
#include "PlaneCollider.h"
#include "AABBCollider.h"
#include "SphereCollider.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Model.h"
#include "GeometryHelper.h"

PlaneCollider::PlaneCollider()
	:BaseCollider(COLLIDER_TYPE::Plane)
{
}

PlaneCollider::~PlaneCollider()
{
}

void PlaneCollider::InitCollider()
{
	_boundingPlane.Distance = 0.f;
	_boundingPlane.Normal = Vec3(0.f, 1.f, 0.f);

	_debugMesh = make_shared<DebugMesh>();
	_debugMesh->Create(GeometryHelper::CreateGrid);
}

void PlaneCollider::UpdateCollider()
{
	Vec3 origin = Vec3{ 0,0,0 };
	Vec3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
	float length = (pos - origin).Length();
	_boundingPlane.Distance = length;

	Vec3 normal = GetOwner()->GetComponent<Transform>()->GetUp();
	_boundingPlane.Normal = normal;
}

bool PlaneCollider::CheckCollision(shared_ptr<BaseCollider> other)
{
	COLLIDER_TYPE type = other->GetColliderType();

	switch (type)
	{
	case COLLIDER_TYPE::Sphere:
		return _boundingPlane.Intersects(dynamic_pointer_cast<SphereCollider>(other)->GetBoundingSphere());
	case COLLIDER_TYPE::AABB:
		return _boundingPlane.Intersects(dynamic_pointer_cast<AABBCollider>(other)->GetBoundingBox());
	case COLLIDER_TYPE::Plane:
		return _boundingPlane.Intersects(dynamic_pointer_cast<PlaneCollider>(other)->GetBoundingPlane());
	}

	return false;
}
