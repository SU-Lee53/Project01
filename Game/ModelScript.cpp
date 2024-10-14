#include "pch.h"
#include "ModelScript.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Model.h"
#include "Material.h"

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
	
	if(ImGui::Begin("Model Transform"))
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

	ShowModelHierarchy();
	ShowModelMeshVertices();
}

// for ImGui Debug
static void ShowBoneNode(shared_ptr<ModelBone> node, vector<shared_ptr<ModelBone>> all_nodes)
{
	ImGui::TableNextRow();
	ImGui::TableNextColumn();
	
	if (node->parentIndex != -1)
	{
		bool open = ImGui::TreeNodeEx(Utils::ToString(node->name).c_str(), ImGuiTreeNodeFlags_SpanAllColumns);
		ImGui::TableNextColumn();
		ImGui::Text("%d", node->index);
		ImGui::TableNextColumn();
		ImGui::Text("%d", node->parentIndex);
		ImGui::TableNextColumn();
		Utils::ShowMatrix(node->transform);
		if (open)
		{
			ShowBoneNode(all_nodes[node->parentIndex], all_nodes);
			ImGui::TreePop();
		}
	}
	else if (node->parentIndex == -1 or node->parentIndex > all_nodes.size())
	{
		ImGui::TreeNodeEx(Utils::ToString(node->name).c_str(), ImGuiTreeNodeFlags_SpanAllColumns | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen);
		ImGui::TableNextColumn();
		ImGui::Text("%d", node->index);
		ImGui::TableNextColumn();
		ImGui::Text("%d", node->parentIndex);
		ImGui::TableNextColumn();
		Utils::ShowMatrix(node->transform);
	}
}

void ModelScript::ShowModelHierarchy()
{
	auto bones = GetOwner()->GetComponent<MeshRenderer>()->GetModel()->GetBones();
	auto meshes = GetOwner()->GetComponent<MeshRenderer>()->GetModel()->GetMeshes();
	auto materials = GetOwner()->GetComponent<MeshRenderer>()->GetModel()->GetMaterials();

	if (ImGui::Begin("Model Structure"))
	{
		for (const auto& model : meshes)
		{
			if (ImGui::TreeNode(Utils::ToString(model->name).c_str()))
			{
				ImGui::BulletText(
					"name : %s\n"
					"materialName : %s\n"
					"materialIndex : %d\n"
					"boneIndex : %d",
					Utils::ToString(model->name).c_str(),
					Utils::ToString(model->materialName).c_str(),
					model->materialIndex,
					model->boneIndex
				);

				if (ImGui::TreeNode("Material"))
				{
					auto m = materials[model->materialIndex];
					if (ImGui::TreeNode("_materialData"))
					{
						if (ImGui::TreeNode("ambient"))
						{
							ImGui::BulletText(
								"ambient : R. %.3f G. %.3f B. %.3f A. %.3f\n",
								m->GetMaterialData().ambient.x, m->GetMaterialData().ambient.y, m->GetMaterialData().ambient.z, m->GetMaterialData().ambient.w
							);
							ImGui::TreePop();
						}
						
						if (ImGui::TreeNode("diffuse"))
						{
							ImGui::BulletText(
								"diffuse : R. %.3f G. %.3f B. %.3f A. %.3f\n",
								m->GetMaterialData().diffuse.x, m->GetMaterialData().diffuse.y, m->GetMaterialData().diffuse.z, m->GetMaterialData().diffuse.w
							);
							ImGui::TreePop();
						}
						
						if (ImGui::TreeNode("specular"))
						{
							ImGui::BulletText(
								"specular : R. %.3f G. %.3f B. %.3f A. %.3f\n",
								m->GetMaterialData().specular.x, m->GetMaterialData().specular.y, m->GetMaterialData().specular.z, m->GetMaterialData().specular.w
							);
							ImGui::TreePop();
						}
						
						if (ImGui::TreeNode("emissive"))
						{
							ImGui::BulletText(
								"emissive : R. %.3f G. %.3f B. %.3f A. %.3f\n",
								m->GetMaterialData().emissive.x, m->GetMaterialData().emissive.y, m->GetMaterialData().emissive.z, m->GetMaterialData().emissive.w
							);
							ImGui::TreePop();
						}

						ImGui::TreePop();
					}

					if (ImGui::TreeNode("_diffuseMap"))
					{
						ImGui::BulletText(
							"(from Resource_Base) _name : %s\n"
							"(from Resource_Base) _path : %s\n"
							"(from Resource_Base) _id : %d\n"
							"_size : (%.3f, %.3f)\n"
							"_isErrorTexture : %s\n",
							Utils::ToString(m->GetDiffuseMap()->GetName()).c_str(),
							Utils::ToString(m->GetDiffuseMap()->GetPath()).c_str(),
							m->GetDiffuseMap()->GetID(),
							m->GetDiffuseMap()->GetSize().x, m->GetDiffuseMap()->GetSize().y,
							m->GetDiffuseMap()->IsErrorTexture() ? "True" : "False"
						);

						ImGui::TreePop();
					}
					
					if (ImGui::TreeNode("_normalMap"))
					{
						ImGui::BulletText(
							"(from Resource_Base) _name : %s\n"
							"(from Resource_Base) _path : %s\n"
							"(from Resource_Base) _id : %d\n"
							"_size : (%.3f, %.3f)\n"
							"_isErrorTexture : %s\n",
							Utils::ToString(m->GetNormalMap()->GetName()).c_str(),
							Utils::ToString(m->GetNormalMap()->GetPath()).c_str(),
							m->GetNormalMap()->GetID(),
							m->GetNormalMap()->GetSize().x, m->GetNormalMap()->GetSize().y,
							m->GetNormalMap()->IsErrorTexture() ? "True" : "False"
						);

						ImGui::TreePop();
					}
					
					if (ImGui::TreeNode("_specularMap"))
					{
						ImGui::BulletText(
							"(from Resource_Base) _name : %s\n"
							"(from Resource_Base) _path : %s\n"
							"(from Resource_Base) _id : %d\n"
							"_size : (%.3f, %.3f)\n"
							"_isErrorTexture : %s\n",
							Utils::ToString(m->GetSpecularMap()->GetName()).c_str(),
							Utils::ToString(m->GetSpecularMap()->GetPath()).c_str(),
							m->GetSpecularMap()->GetID(),
							m->GetSpecularMap()->GetSize().x, m->GetSpecularMap()->GetSize().y,
							m->GetSpecularMap()->IsErrorTexture() ? "True" : "False"
						);

						ImGui::TreePop();
					}

					ImGui::TreePop();
				}

				if (ImGui::TreeNode("Bones"))
				{
					if (ImGui::BeginTable("Bones", 4, flags))
					{
						ImGui::TableSetupColumn("name");
						ImGui::TableSetupColumn("index");
						ImGui::TableSetupColumn("parentIndex");
						ImGui::TableSetupColumn("transform");
						ImGui::TableHeadersRow();
					
						ShowBoneNode(bones[model->boneIndex], bones);
					
						ImGui::EndTable();
					}
					ImGui::TreePop();
				}

				ImGui::TreePop();
			} 
		}
	}
	ImGui::End();

}

void ModelScript::ShowModelMeshVertices()
{
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
