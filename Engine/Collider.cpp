#include "EnginePch.h"
#include "Collider.h"
#include "GameObject.h"

Collider::Collider()
{
}

Collider::~Collider()
{
}

void Collider::Update_impl()
{
	_position = Vec3::Transform(_position, GetOwner()->GetTransform()->GetWorld());
}
