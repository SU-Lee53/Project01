#include "pch.h"
#include "ModelScript.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Model.h"

void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::BeginItemTooltip())
	{
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void ModelScript::Init()
{
	_transform = GetOwner()->GetTransform()->GetWorld();
	_model = GetOwner()->GetComponent<MeshRenderer>()->GetModel();
}

void ModelScript::Update()
{
	//auto model = _model.lock();
	
	ImGui::Begin("Model Transform");
	{
		Vec3 pos = GetOwner()->GetTransform()->GetPosition();
		Vec3 rot = GetOwner()->GetTransform()->GetRotation();
		Vec3 scale = GetOwner()->GetTransform()->GetScale();

		if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { _dragSpeed -= 0.05f; }
		ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
		if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { _dragSpeed += 0.05f; }
		ImGui::SameLine();
		ImGui::Text("Drag Speed : %f", _dragSpeed);

		ImGui::InputFloat3("Pos", (float*)&pos);
		ImGui::DragFloat("Pos.x", &pos.x, _dragSpeed, -10.f, 10.f);
		ImGui::SameLine(); HelpMarker(
			"Click and drag to edit value.\n"
			"Hold SHIFT/ALT for faster/slower edit.\n"
			"Double-click or CTRL+click to input value.");
		ImGui::DragFloat("Pos.y", &pos.y, _dragSpeed, -10.f, 10.f);
		ImGui::DragFloat("Pos.z", &pos.z, _dragSpeed, -10.f, 10.f);

		ImGui::InputFloat3("Rot", (float*)&rot, "%.3f Deg");
		ImGui::DragFloat("Rot.x", &rot.x, _dragSpeed, -180.f, 180.f);
		ImGui::DragFloat("Rot.y", &rot.y, _dragSpeed, -180.f, 180.f);
		ImGui::DragFloat("Rot.z", &rot.z, _dragSpeed, -180.f, 180.f);
		
		ImGui::Checkbox("Scale type", &_scaleType);

		if(_scaleType)
		{
			ImGui::InputFloat3("Scale", (float*)&scale, "%.3f");
			ImGui::DragFloat("Scale.x", &scale.x, _dragSpeed, -180.f, 180.f);
			ImGui::DragFloat("Scale.y", &scale.y, _dragSpeed, -180.f, 180.f);
			ImGui::DragFloat("Scale.z", &scale.z, _dragSpeed, -180.f, 180.f);
		}
		else
		{
			ImGui::DragFloat("Scale", &scale.x, _dragSpeed, 0.0f, 2.0f);

			scale = Vec3{ scale.x, scale.x, scale.x };
		}

		GetOwner()->GetTransform()->SetPosition(pos);
		GetOwner()->GetTransform()->SetRotation(rot);
		GetOwner()->GetTransform()->SetScale(scale);

		ImGui::Text("Position");
		ImGui::Text("X: %3f", pos.x);
		ImGui::Text("Y: %3f", pos.y);
		ImGui::Text("Z: %3f", pos.z);
		ImGui::Text("");

		ImGui::Text("Rotation");
		ImGui::Text("X: %3f", rot.x);
		ImGui::Text("Y: %3f", rot.y);
		ImGui::Text("Z: %3f", rot.z);

		ImGui::Text("Scale");
		ImGui::Text("X: %3f", scale.x);
		ImGui::Text("Y: %3f", scale.y);
		ImGui::Text("Z: %3f", scale.z);
	}
	ImGui::End();

}

bool ModelScript::HasParent(int index)
{
	auto bones = _model.lock()->GetBones();

	if (bones[index]->parentIndex >= 0 || bones[index]->parentIndex < bones.size());
		return false;

	return true;
}

bool ModelScript::HasChild(int index)
{
	auto bones = _model.lock()->GetBones();

	auto it = find_if(bones.begin(), bones.end(),
		[index](shared_ptr<ModelBone> b) -> bool
		{
			if (b->parentIndex == index) return true;
			return false;
		}
	);

	if (it != bones.end()) return true;

	return false;
}

bool ModelScript::IsRoot(int index)
{
	return false;
}
