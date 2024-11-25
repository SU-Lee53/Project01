#include "EnginePch.h"
#include "SphereCollider.h"
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
	Vec3 pos = GetOwner()->GetTransform()->GetLocalPosition() * GetOwner()->GetTransform()->GetPosition();

	_boundingSphere.Center = pos;

}

bool SphereCollider::CheckCollision(shared_ptr<BaseCollider> other)
{
	return false;
}
