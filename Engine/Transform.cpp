#include "EnginePch.h"
#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::Update_impl()
{
	UpdateMatrix();
}

void Transform::UpdateMatrix()
{
	// TODO : Fill
}

void Transform::SetPosition(const Vec3& pos)
{
	_position = pos;
	UpdateMatrix();
}

void Transform::SetRotation(const Vec3& rot)
{
	_rotation = rot;
	UpdateMatrix();
}

void Transform::SetScale(const Vec3& scale)
{
	_scale = scale;
	UpdateMatrix();
}

void Transform::PushTransform()
{
}
