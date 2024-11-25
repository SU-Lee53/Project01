#include "pch.h"
#include "SceneModelController.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"

void SceneModelController::Init()
{
	UpdateComboList();
}

void SceneModelController::Update()
{
	if (prevComboListSize != _items.size())
	{
		UpdateComboList();
	}

	previewName = _items[itemSelected].first.c_str();

	if (ImGui::Begin("Model Controller"))
	{
		if (ImGui::BeginCombo("Objs", previewName, ImGuiComboFlags_PopupAlignLeft))
		{
			for (int32 n = 0; n < _items.size(); n++)
			{
				const bool is_selected = (itemSelected == n);
				if (ImGui::Selectable(_items[n].first.c_str(), is_selected))
					itemSelected = n;

				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();

				}
			}
			ImGui::EndCombo();
		}

		const bool canOpen = (_items[itemSelected].second->GetComponent<MeshRenderer>() != nullptr);
		shared_ptr<GameObject> target = nullptr;
		if (canOpen)
		{
			target = _items[itemSelected].second;
		}

		if (target)
		{
			if (ImGui::BeginTabBar("Transform", ImGuiTabBarFlags_None))
			{
				if (ImGui::BeginTabItem("World Transform"))
				{
					Vec3 pos = target->GetTransform()->GetPosition();
					Vec3 rot = target->GetTransform()->GetRotation();
					Vec3 scale = target->GetTransform()->GetScale();

					if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { _dragSpeed -= 0.05f; }
					ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
					if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { _dragSpeed += 0.05f; }
					ImGui::SameLine();
					ImGui::Text("Drag Speed : %f", _dragSpeed);

					ImGui::InputFloat3("Pos", (float*)&pos);
					ImGui::DragFloat("Pos.x", &pos.x, _dragSpeed, -100.f, 100.f);
					ImGui::DragFloat("Pos.y", &pos.y, _dragSpeed, -100.f, 100.f);
					ImGui::DragFloat("Pos.z", &pos.z, _dragSpeed, -100.f, 100.f);

					ImGui::InputFloat3("Rot", (float*)&rot, "%.3f Deg");
					ImGui::DragFloat("Rot.x", &rot.x, _dragSpeed, -180.f, 180.f);
					ImGui::DragFloat("Rot.y", &rot.y, _dragSpeed, -180.f, 180.f);
					ImGui::DragFloat("Rot.z", &rot.z, _dragSpeed, -180.f, 180.f);

					ImGui::Checkbox("Scale type", &_scaleType);

					if (_scaleType)
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

					_items[itemSelected].second->GetTransform()->SetPosition(pos);
					_items[itemSelected].second->GetTransform()->SetRotation(rot);
					_items[itemSelected].second->GetTransform()->SetScale(scale);

					ImGui::Text("Position");
					ImGui::Text("X: %3f", pos.x);
					ImGui::Text("Y: %3f", pos.y);
					ImGui::Text("Z: %3f", pos.z);
					ImGui::Text("");

					ImGui::Text("Rotation");
					ImGui::Text("X: %3f", rot.x);
					ImGui::Text("Y: %3f", rot.y);
					ImGui::Text("Z: %3f", rot.z);
					ImGui::Text("");

					ImGui::Text("Scale");
					ImGui::Text("X: %3f", scale.x);
					ImGui::Text("Y: %3f", scale.y);
					ImGui::Text("Z: %3f", scale.z);

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Local Transform"))
				{
					Vec3 localPos = target->GetTransform()->GetLocalPosition();
					Vec3 localRot = target->GetTransform()->GetLocalRotation();
					Vec3 localScale = target->GetTransform()->GetLocalScale();

					if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { _dragSpeed -= 0.05f; }
					ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
					if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { _dragSpeed += 0.05f; }
					ImGui::SameLine();
					ImGui::Text("Drag Speed : %f", _dragSpeed);

					ImGui::InputFloat3("Pos", (float*)&localPos);
					ImGui::DragFloat("Pos.x", &localPos.x, _dragSpeed, -10.f, 10.f);
					ImGui::DragFloat("Pos.y", &localPos.y, _dragSpeed, -10.f, 10.f);
					ImGui::DragFloat("Pos.z", &localPos.z, _dragSpeed, -10.f, 10.f);

					ImGui::InputFloat3("Rot", (float*)&localRot, "%.3f Deg");
					ImGui::DragFloat("Rot.x", &localRot.x, _dragSpeed, -180.f, 180.f);
					ImGui::DragFloat("Rot.y", &localRot.y, _dragSpeed, -180.f, 180.f);
					ImGui::DragFloat("Rot.z", &localRot.z, _dragSpeed, -180.f, 180.f);

					ImGui::Checkbox("Scale type", &_scaleType);

					if (_scaleType)
					{
						ImGui::InputFloat3("Scale", (float*)&localScale, "%.3f");
						ImGui::DragFloat("Scale.x", &localScale.x, _dragSpeed, -180.f, 180.f);
						ImGui::DragFloat("Scale.y", &localScale.y, _dragSpeed, -180.f, 180.f);
						ImGui::DragFloat("Scale.z", &localScale.z, _dragSpeed, -180.f, 180.f);
					}
					else
					{
						ImGui::DragFloat("Scale", &localScale.x, _dragSpeed, 0.0f, 2.0f);

						localScale = Vec3{ localScale.x, localScale.x, localScale.x };
					}

					_items[itemSelected].second->GetTransform()->SetLocalPosition(localPos);
					_items[itemSelected].second->GetTransform()->SetLocalRotation(localRot);
					_items[itemSelected].second->GetTransform()->SetLocalScale(localScale);

					ImGui::Text("Position");
					ImGui::Text("X: %3f", localPos.x);
					ImGui::Text("Y: %3f", localPos.y);
					ImGui::Text("Z: %3f", localPos.z);
					ImGui::Text("");

					ImGui::Text("Rotation");
					ImGui::Text("X: %3f", localRot.x);
					ImGui::Text("Y: %3f", localRot.y);
					ImGui::Text("Z: %3f", localRot.z);
					ImGui::Text("");

					ImGui::Text("Scale");
					ImGui::Text("X: %3f", localScale.x);
					ImGui::Text("Y: %3f", localScale.y);
					ImGui::Text("Z: %3f", localScale.z);

					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
		}
		else
		{
			ImGui::Text("This GameObject has NO models to controll");
		}


	}
	ImGui::End();

}

void SceneModelController::UpdateComboList()
{
	_items.clear();

	unordered_set<shared_ptr<GameObject>> objSet = GetOwner()->GetObjects();
	for (const auto& obj : objSet)
	{
		_items.push_back(make_pair(obj->GetName(), obj));
	}

	prevComboListSize = _items.size();
}
