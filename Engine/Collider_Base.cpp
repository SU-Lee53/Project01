#include "EnginePch.h"
#include "Collider_Base.h"
#include "GameObject.h"

Collider_Base::Collider_Base()
{
}

Collider_Base::~Collider_Base()
{
}

void Collider_Base::Update_impl()
{
	_position = Vec3::Transform(_position, GetOwner()->GetTransform()->GetWorld());
}
