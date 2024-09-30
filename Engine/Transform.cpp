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
	Matrix translate	= Matrix::Identity;
	Matrix rotate		= Matrix::Identity;
	Matrix scale		= Matrix::Identity;

	Vec3 rotDegree = {
		XMConvertToRadians(_rotation.x),
		XMConvertToRadians(_rotation.y),
		XMConvertToRadians(_rotation.z)
	};

	translate *= Matrix::CreateTranslation(_position);
	rotate *= Matrix::CreateRotationX(rotDegree.x);
	rotate *= Matrix::CreateRotationY(rotDegree.y);
	rotate *= Matrix::CreateRotationZ(rotDegree.z);
	scale *= Matrix::CreateScale(_scale);
	
	_world = scale * rotate * translate;
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
