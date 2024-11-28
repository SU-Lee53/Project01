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

	Vec3 rotRadians = {
		XMConvertToRadians(_rotation.x),
		XMConvertToRadians(_rotation.y),
		XMConvertToRadians(_rotation.z)
	};

	_quaternion = Quaternion::CreateFromYawPitchRoll(rotRadians.y, rotRadians.x, rotRadians.z);

	translate *= Matrix::CreateTranslation(_position);
	rotate *= Matrix::CreateRotationX(rotRadians.x);
	rotate *= Matrix::CreateRotationY(rotRadians.y);
	rotate *= Matrix::CreateRotationZ(rotRadians.z);
	//rotate *= Matrix::CreateFromQuaternion(_quaternion);
	scale *= Matrix::CreateScale(_scale);
	
	_world = scale;
	_world *= rotate;
	_world *= translate;

	translate = Matrix::Identity;
	rotate = Matrix::Identity;
	scale = Matrix::Identity;
	
	rotRadians = {
		XMConvertToRadians(_localRotation.x),
		XMConvertToRadians(_localRotation.y),
		XMConvertToRadians(_localRotation.z)
	};

	_localQuaternion = Quaternion::CreateFromYawPitchRoll(rotRadians.y, rotRadians.x, rotRadians.y);

	translate *= Matrix::CreateTranslation(_localPosition);
	rotate *= Matrix::CreateRotationX(rotRadians.x);
	rotate *= Matrix::CreateRotationY(rotRadians.y);
	rotate *= Matrix::CreateRotationZ(rotRadians.z);
	//rotate *= Matrix::CreateFromQuaternion(_localQuaternion);
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

void Transform::ShowStatusToImGui()
{
	if (ImGui::BeginTabBar("Transform"))
	{
		if (ImGui::BeginTabItem("World"))
		{
			ImGui::Text("World Position");
			ImGui::Text("(x, y, z) : (%3f, %3f, %3f)", _position.x, _position.y, _position.z);
			ImGui::Text("");

			ImGui::Text("World Rotation");
			ImGui::Text("(x, y, z) : (%3f, %3f, %3f)", _rotation.x, _rotation.y, _rotation.z);
			ImGui::Text("");

			ImGui::Text("World Quaternion");
			ImGui::Text("(x, y, z, w) : (%3f, %3f, %3f, %3f)", _quaternion.x, _quaternion.y, _quaternion.z, _quaternion.w);
			ImGui::Text("");

			ImGui::Text("World Scale");
			ImGui::Text("(x, y, z) : (%3f, %3f, %3f)", _scale.x, _scale.y, _scale.z);
			ImGui::Text("");

			Utils::ShowMatrix(_world);

			ImGui::EndTabItem();
		}
		
		if (ImGui::BeginTabItem("Local"))
		{
			ImGui::Text("Local Position");
			ImGui::Text("(x, y, z) : (%3f, %3f, %3f)", _localPosition.x, _localPosition.y, _localPosition.z);
			ImGui::Text("");

			ImGui::Text("Local Rotation");
			ImGui::Text("(x, y, z) : (%3f, %3f, %3f)", _localRotation.x, _localRotation.y, _localRotation.z);
			ImGui::Text("");

			ImGui::Text("Local Quaternion");
			ImGui::Text("(x, y, z, w) : (%3f, %3f, %3f, %3f)", _localQuaternion.x, _localQuaternion.y, _localQuaternion.z, _localQuaternion.w);
			ImGui::Text("");

			ImGui::Text("Local Scale");
			ImGui::Text("(x, y, z) : (%3f, %3f, %3f)", _localScale.x, _localScale.y, _localScale.z);
			ImGui::Text("");

			Utils::ShowMatrix(_local);

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
}
