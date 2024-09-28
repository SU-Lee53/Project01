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
	Matrix m = Matrix::Identity;
	{
		m *= Matrix::CreateTranslation(_position);
		m *= Matrix::CreateRotationX(_rotation.x);
		m *= Matrix::CreateRotationY(_rotation.y);
		m *= Matrix::CreateRotationZ(_rotation.z);
		m *= Matrix::CreateScale(_scale);
	}

	_world = m;
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
