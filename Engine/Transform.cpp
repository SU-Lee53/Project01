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

	// Assume that every models has 1 mesh/bone in meshes/bones
	auto meshRenderer = GetOwner()->GetComponent<MeshRenderer>();
	if (meshRenderer->GetModel())
	{
		auto model = GetOwner()->GetComponent<MeshRenderer>()->GetModel();
		auto bone = model->GetBones()[model->GetMeshes()[0]->boneIndex];
		Matrix transform = bone->transform;

		Vec3 outPos;
		Quaternion outRot;
		Vec3 outScale;

		transform.Decompose(outScale, outRot, outPos);
		Vec3 Rot = Utils::ToEulerAngles(outRot);

		_localPosition = outPos;
		_localRotation = Rot;
		_localScale = outScale;

	}


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
