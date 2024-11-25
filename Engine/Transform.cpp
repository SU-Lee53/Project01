#include "EnginePch.h"
#include "Transform.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Model.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::Init_impl()
{
	// 11.25
	// TODO : Get Bone transform to world!!
	if(GetOwner()->HasComponent<MeshRenderer>())
	{
		auto root = GetOwner()->GetComponent<MeshRenderer>()->GetModel()->GetBones();
		Matrix local = root[GetOwner()->GetComponent<MeshRenderer>()->GetModel()->GetMeshes().front()->boneIndex]->transform;

		Vec3 outPos;
		Vec3 outScale;
		Quaternion outRot;

		local.Decompose(outScale, outRot, outPos);

		_position = outPos;
		_scale = outScale;

		// 11.26
		// something wrong i guess
		Vec3 temp = Utils::ToEulerAngles(outRot);

		_rotation = Vec3{
			XMConvertToDegrees(temp.x),
			XMConvertToDegrees(temp.y),
			XMConvertToDegrees(temp.z)
		};
	}
}

void Transform::Update_impl()
{
	UpdateMatrix();
}

void Transform::UpdateMatrix()
{
	// World
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
	
	_world = scale;
	_world *= rotate;
	_world *= translate;

	// Local
	translate = Matrix::Identity;
	rotate = Matrix::Identity;
	scale = Matrix::Identity;

	rotDegree = {
		XMConvertToRadians(_localRotation.x),
		XMConvertToRadians(_localRotation.y),
		XMConvertToRadians(_localRotation.z)
	};

	translate *= Matrix::CreateTranslation(_localPosition);
	rotate *= Matrix::CreateRotationX(rotDegree.x);
	rotate *= Matrix::CreateRotationY(rotDegree.y);
	rotate *= Matrix::CreateRotationZ(rotDegree.z);
	scale *= Matrix::CreateScale(_localScale);

	_local = scale;
	_local *= rotate;
	_local *= translate;

}

void Transform::SetPosition(const Vec3& pos)
{
	_position = pos;
}

void Transform::SetRotation(const Vec3& rot)
{
	_rotation = rot;
}

void Transform::SetScale(const Vec3& scale)
{
	_scale = scale;
}

void Transform::SetLocalPosition(const Vec3& pos)
{
	_localPosition = pos;
}

void Transform::SetLocalRotation(const Vec3& rot)
{
	_localRotation = rot;
}

void Transform::SetLocalScale(const Vec3& scale)
{
	_localScale = scale;
}

void Transform::PushTransform()
{
}
