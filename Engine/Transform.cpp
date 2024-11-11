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
	// Sync local transform with models final bone
	// Assume that every models has only one mesh/bone in meshes/bones
	auto meshRenderer = GetOwner()->GetComponent<MeshRenderer>();
	if (meshRenderer and meshRenderer->GetModel())
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
		
		//Matrix localTranslate = Matrix::CreateTranslation(_localPosition);
		//Matrix localRotate = Matrix::CreateRotationX(_localRotation.x);
		//localRotate *= Matrix::CreateRotationY(_localRotation.y);
		//localRotate *= Matrix::CreateRotationZ(_localRotation.z);
		//Matrix localScale = Matrix::CreateScale(outScale);

		_local = transform;
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
	
	_world = rotate * translate * scale;

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

	_local = scale * rotate * translate;

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
