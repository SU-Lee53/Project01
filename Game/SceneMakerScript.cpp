#include "pch.h"
#include "SceneMakerScript.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Model.h"
#include "Transform.h"
#include "Camera.h"
#include "GlobalLight.h"
#include "BaseCollider.h"
#include "SphereCollider.h"
#include "AABBCollider.h"
#include "PlaneCollider.h"
#include "MouseScript.h"
#include <filesystem>


#include "nlohmann/json.hpp"
using json = nlohmann::json;

void SceneMakerScript::Init()
{
	// json test
	//wstring temp = L"../pool_project.json";
	//auto p = filesystem::path(temp);
	//
	//ifstream is(p);
	//assert(is.is_open(), "failed to open " + Utils::ToString(temp));
	//
	//json data = json::parse(is);

	auto p = filesystem::path("../Resources/Models");

	for (const auto& dir : filesystem::directory_iterator(p))
	{
		if (dir.is_regular_file() and dir.path().extension().string() == ".mesh")
		{
			wstring temp = dir.path().filename().wstring();
			LoadTargets.push_back(temp);
		}
	}

	lo_prevComboListSize = LoadTargets.size();
}

void SceneMakerScript::Update()
{
	string temp = Utils::ToString(LoadTargets[lo_itemSelected]);
	lo_previewName = temp.c_str();

	if (ImGui::Begin("SceneMaker"))
	{
		if (ImGui::BeginTabBar("SceneMaker", ImGuiTabBarFlags_None))
		{
			if (ImGui::BeginTabItem("Scene Controller"))
			{
				ImGui::Text("Controller");
				SceneController();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Component Modifier"))
			{
				ImGui::Text("Component Modifier");
				ComponentModifier();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Save / Load"))
			{
				ImGui::Text("Save / Load");
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}

	}
	ImGui::End();
}

void SceneMakerScript::SaveScene()
{
}

void SceneMakerScript::LoadScene()
{
}

void SceneMakerScript::ObjLoader()
{
	if (ImGui::BeginListBox("LoadedObjs"))
	{
		for (int n = 0; n < LoadedObjs.size(); n++)
		{
			const bool is_selected = (lo_itemSelected == n);
			if (ImGui::Selectable(LoadedObjs[n].first.c_str(), is_selected))
				lo_itemSelected = n;

			if (lo_itemHighlighted && ImGui::IsItemHovered())
				lo_itemHighlightedIdx = n;

			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}

}

void SceneMakerScript::SceneController()
{
	if (ImGui::BeginTabBar("Scene"))
	{
		if (ImGui::BeginTabItem("Cameras"))
		{
			auto cams = CUR_SCENE->GetCameras();
			vector<shared_ptr<GameObject>> camVector(cams.begin(), cams.end());

			if (ImGui::BeginListBox("Camera in scene"))
			{
				for (int n = 0; n < camVector.size(); n++)
				{
					const bool is_selected = (sc_cam_itemSelected == n);
					if (ImGui::Selectable(camVector[n]->GetName().c_str(), is_selected))
						sc_cam_itemSelected = n;

					if (sc_itemHighlighted && ImGui::IsItemHovered())
						sc_cam_itemHighlightedIdx = n;

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndListBox();
			}

			shared_ptr<GameObject> selected;
			if (sc_itemSelected < camVector.size())
				selected = camVector[sc_cam_itemSelected];

			if (ImGui::Button("Set Main Camera"))
			{
				CUR_SCENE->SetMainCamera(selected->GetName());
			}

			ImGui::NewLine();
			ImGui::Text("Add new");
			ImGui::InputText("Name", _name, IM_ARRAYSIZE(_name));
			ImGui::InputFloat3("Pos", (float*)& cam_pos);

			if (ImGui::Button("Add new camera"))
			{
				shared_ptr<GameObject> add = make_shared<GameObject>();
				add->AddComponent<Transform>();
				add->GetComponent<Transform>()->SetPosition(cam_pos);
				add->AddComponent<Camera>();

				auto _mouseScript = make_shared<MouseScript>();
				add->AddScript(_mouseScript);

				add->SetName(_name);
				CUR_SCENE->AddCamera(add);
			}

			ImGui::SameLine();
			if (ImGui::Button("Remove camera"))
			{
				if (selected)
				{
					CUR_SCENE->RemoveObject(selected);
					sc_cam_itemSelected--;
					sc_cam_itemHighlightedIdx--;
				}
				else
					ImGui::Text("No Item Selected");
			}


			if (selected)
			{
				if (ImGui::BeginTabBar("Components", ImGuiTabBarFlags_None))
				{
					if (ImGui::BeginTabItem("Transform"))
					{
						ImGui::Text("Transform");
						if (selected->GetComponent<Transform>())
						{
							// TODO : Add inspector
							selected->GetComponent<Transform>()->ShowStatusToImGui();
						}
						else
						{
							ImGui::Text("No Transform");
						}
						ImGui::EndTabItem();
					}

					ImGui::EndTabBar();
				}
			}

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("GlobalLight"))
		{
			auto light = CUR_SCENE->GetGlobalLight();
			ControlGlobalLight(light);

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}


}

void SceneMakerScript::ControlGlobalLight(shared_ptr<GameObject> light)
{
	sc_lightData = light->GetComponent<GlobalLight>()->GetData();

	ImGui::DragFloat("Drag Speed : %f", &_dragSpeed, 0.005f, 0.f, 5.f);

	ImGui::NewLine();
	ImGui::InputFloat3("Ambient", (float*)&sc_lightData.ambient);
	ImGui::DragFloat("Ambient.R", &sc_lightData.ambient.x, _dragSpeed, 0.f, 1.f);
	ImGui::DragFloat("Ambient.G", &sc_lightData.ambient.y, _dragSpeed, 0.f, 1.f);
	ImGui::DragFloat("Ambient.B", &sc_lightData.ambient.z, _dragSpeed, 0.f, 1.f);

	ImGui::NewLine();
	ImGui::InputFloat3("Diffuse", (float*)&sc_lightData.diffuse);
	ImGui::DragFloat("Diffuse.R", &sc_lightData.diffuse.x, _dragSpeed, 0.f, 1.f);
	ImGui::DragFloat("Diffuse.G", &sc_lightData.diffuse.y, _dragSpeed, 0.f, 1.f);
	ImGui::DragFloat("Diffuse.B", &sc_lightData.diffuse.z, _dragSpeed, 0.f, 1.f);

	ImGui::NewLine();
	ImGui::InputFloat3("Specular", (float*)&sc_lightData.specular);
	ImGui::DragFloat("Specular.R", &sc_lightData.specular.x, _dragSpeed, 0.f, 1.f);
	ImGui::DragFloat("Specular.G", &sc_lightData.specular.y, _dragSpeed, 0.f, 1.f);
	ImGui::DragFloat("Specular.B", &sc_lightData.specular.z, _dragSpeed, 0.f, 1.f);
	ImGui::DragInt("Pow", &sc_lightData.specularPowValue, 1.f, 0, 100);

	ImGui::NewLine();
	ImGui::InputFloat3("Direction", (float*)&sc_lightData.direction);
	ImGui::DragFloat("Direction.x", &sc_lightData.direction.x, _dragSpeed, -1.f, 1.f);
	ImGui::DragFloat("Direction.y", &sc_lightData.direction.y, _dragSpeed, -1.f, 1.f);
	ImGui::DragFloat("Direction.z", &sc_lightData.direction.z, _dragSpeed, -1.f, 1.f);
	//sc_lightData.direction.Normalize();

	light->GetComponent<GlobalLight>()->SetData(sc_lightData);
}

void SceneMakerScript::ComponentModifier()
{
	if (ImGui::BeginTabBar("Scene"))
	{
		if (ImGui::BeginTabItem("Objects"))
		{
			auto objs = CUR_SCENE->GetObjects();
			vector<shared_ptr<GameObject>> objVector(objs.begin(), objs.end());

			if (ImGui::BeginListBox("object in scene"))
			{
				for (int n = 0; n < objVector.size(); n++)
				{
					const bool is_selected = (sc_itemSelected == n);
					if (ImGui::Selectable(objVector[n]->GetName().c_str(), is_selected))
						sc_itemSelected = n;

					if (sc_itemHighlighted && ImGui::IsItemHovered())
						sc_itemHighlightedIdx = n;

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndListBox();
			}

			shared_ptr<GameObject> selected;
			if (sc_itemSelected < objVector.size())
				selected = objVector[sc_itemSelected];

			ImGui::InputText("Name", _name, IM_ARRAYSIZE(_name));
			if (ImGui::Button("Add to Scene"))
			{
				shared_ptr<GameObject> add = make_shared<GameObject>();
				add->SetName(_name);
				CUR_SCENE->AddObject(add);
			}
			if (ImGui::Button("Remove from Scene"))
			{
				if (selected)
				{
					CUR_SCENE->RemoveObject(selected);
					sc_itemSelected--;
					sc_itemHighlightedIdx--;
				}
				else
					ImGui::Text("No Item Selected");
			}

			ImGui::NewLine();

			// Show Basic Status
			if (selected)
			{
				if (ImGui::BeginTabBar("Components", ImGuiTabBarFlags_None))
				{
					if (ImGui::BeginTabItem("Transform"))
					{
						ImGui::Text("Transform");
						TransformModifier(selected);
						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("MeshRenderer"))
					{
						ImGui::Text("MeshRenderer");
						MeshRendererModifier(selected);
						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Collider"))
					{
						ImGui::Text("Collider");
						ImGui::Text("TODO : Complete collider first!!!!!!!");
						ColliderModifier(selected);

						ImGui::EndTabItem();
					}


					ImGui::EndTabBar();
				}
			}

			ImGui::EndTabItem();
		}


		// Camera Modifier
		if (ImGui::BeginTabItem("Cameras"))
		{
			auto cams = CUR_SCENE->GetCameras();
			vector<shared_ptr<GameObject>> camVector(cams.begin(), cams.end());

			if (ImGui::BeginListBox("Camera in scene"))
			{
				for (int n = 0; n < camVector.size(); n++)
				{
					const bool is_selected = (sc_cam_itemSelected == n);
					if (ImGui::Selectable(camVector[n]->GetName().c_str(), is_selected))
						sc_cam_itemSelected = n;

					if (sc_itemHighlighted && ImGui::IsItemHovered())
						sc_cam_itemHighlightedIdx = n;

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndListBox();
			}

			shared_ptr<GameObject> selected;
			if (sc_itemSelected < camVector.size())
				selected = camVector[sc_cam_itemSelected];

			if (selected)
			{
				if (ImGui::BeginTabBar("Components", ImGuiTabBarFlags_None))
				{
					if (ImGui::BeginTabItem("Transform"))
					{
						ImGui::Text("Transform");
						if (selected->GetComponent<Transform>())
						{
							// TODO : Add inspector
							selected->GetComponent<Transform>()->ShowStatusToImGui();
						}
						else
						{
							ImGui::Text("No Transform");
						}
						ImGui::EndTabItem();
					}

					ImGui::EndTabBar();
				}
			}

			ImGui::EndTabItem();
		}



		ImGui::EndTabBar();
	}
}

void SceneMakerScript::TransformModifier(shared_ptr<GameObject> target)
{
	if (target->GetComponent<Transform>() == nullptr)
	{
		if (ImGui::Button("Add"))
		{
			target->AddComponent<Transform>();
		}
	}
	else
	{
		if (ImGui::BeginTabBar("Transform", ImGuiTabBarFlags_None))
		{
			if (ImGui::BeginTabItem("World Transform"))
			{
				Vec3 pos = target->GetTransform()->GetPosition();
				Vec3 rot = target->GetTransform()->GetRotation();
				Vec3 scale = target->GetTransform()->GetScale();
				Quaternion q = target->GetTransform()->GetQuaternion();

				ImGui::DragFloat("Drag Speed : %f", &_dragSpeed, 0.005f, 0.f, 5.f);

				ImGui::NewLine();
				ImGui::InputFloat3("Pos", (float*)&pos);
				ImGui::DragFloat("Pos.x", &pos.x, _dragSpeed, -100.f, 100.f);
				ImGui::DragFloat("Pos.y", &pos.y, _dragSpeed, -100.f, 100.f);
				ImGui::DragFloat("Pos.z", &pos.z, _dragSpeed, -100.f, 100.f);

				ImGui::NewLine();
				ImGui::InputFloat3("Rot", (float*)&rot, "%.3f Deg");
				ImGui::DragFloat("Rot.x", &rot.x, _dragSpeed, -180.f, 180.f);
				ImGui::DragFloat("Rot.y", &rot.y, _dragSpeed, -180.f, 180.f);
				ImGui::DragFloat("Rot.z", &rot.z, _dragSpeed, -180.f, 180.f);

				ImGui::NewLine();
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

				target->GetTransform()->SetPosition(pos);
				target->GetTransform()->SetRotation(rot);
				target->GetTransform()->SetScale(scale);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Local Transform"))
			{
				Vec3 localPos = target->GetTransform()->GetLocalPosition();
				Vec3 localRot = target->GetTransform()->GetLocalRotation();
				Vec3 localScale = target->GetTransform()->GetLocalScale();

				ImGui::DragFloat("Drag Speed : %f", &_dragSpeed, 0.005f, 0.f, 5.f);

				ImGui::NewLine();
				ImGui::InputFloat3("Pos", (float*)&localPos);
				ImGui::DragFloat("Pos.x", &localPos.x, _dragSpeed, -10.f, 10.f);
				ImGui::DragFloat("Pos.y", &localPos.y, _dragSpeed, -10.f, 10.f);
				ImGui::DragFloat("Pos.z", &localPos.z, _dragSpeed, -10.f, 10.f);

				ImGui::NewLine();
				ImGui::InputFloat3("Rot", (float*)&localRot, "%.3f Deg");
				ImGui::DragFloat("Rot.x", &localRot.x, _dragSpeed, -180.f, 180.f);
				ImGui::DragFloat("Rot.y", &localRot.y, _dragSpeed, -180.f, 180.f);
				ImGui::DragFloat("Rot.z", &localRot.z, _dragSpeed, -180.f, 180.f);

				ImGui::NewLine();
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

				target->GetTransform()->SetLocalPosition(localPos);
				target->GetTransform()->SetLocalRotation(localRot);
				target->GetTransform()->SetLocalScale(localScale);

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
	}
}

void SceneMakerScript::MeshRendererModifier(shared_ptr<GameObject> target)
{
	if (ImGui::BeginListBox(".mesh in ../Resources/Models"))
	{
		for (int n = 0; n < LoadTargets.size(); n++)
		{
			const bool is_selected = (mm_itemSelected == n);
			string showName = Utils::ToString(LoadTargets[n]);
			if (ImGui::Selectable(showName.c_str(), is_selected))
				mm_itemSelected = n;

			if (mm_itemHighlighted && ImGui::IsItemHovered())
				mm_itemHighlightedIdx = n;

			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}

	if (target->GetComponent<MeshRenderer>() == nullptr)
	{
		if (ImGui::Button("Add"))
		{
			auto selected = LoadTargets[mm_itemSelected];
			auto m = make_shared<Model>();
			m->LoadFromFiles(selected);
			target->AddComponent<MeshRenderer>();
			target->GetComponent<MeshRenderer>()->SetModel(m);
		}

	}
	else
	{
		ImGui::Checkbox("Render", &mm_renderOnOff);
		target->GetComponent<MeshRenderer>()->SetRenderOnOff(mm_renderOnOff);
		if (ImGui::Button("Change"))
		{
			target->RemoveComponent<MeshRenderer>();
			auto selected = LoadTargets[mm_itemSelected];
			auto m = make_shared<Model>();
			m->LoadFromFiles(selected);

			target->AddComponent<MeshRenderer>();
			target->GetComponent<MeshRenderer>()->SetModel(m);
		}

		if (ImGui::Button("Remove"))
		{
			target->RemoveComponent<MeshRenderer>();
		}
	}

}

void SceneMakerScript::ColliderModifier(shared_ptr<GameObject> target)
{
	shared_ptr<BaseCollider> col;
	if (target->GetCollider<SphereCollider>())
	{
		col = target->GetCollider<SphereCollider>();
	}
	else if (target->GetCollider<AABBCollider>())
	{
		col = target->GetCollider<AABBCollider>();
	}
	else if (target->GetCollider<PlaneCollider>())
	{
		col = target->GetCollider<PlaneCollider>();
	}

	if (col == nullptr)
	{
		if (ImGui::BeginListBox("ColliderType"))
		{
			for (int n = 0; n < IM_ARRAYSIZE(cm_items); n++)
			{
				const bool is_selected = (cm_itemSelected == n);
				if (ImGui::Selectable(cm_items[n], is_selected))
					cm_itemSelected = n;

				if (cm_itemHighlighted && ImGui::IsItemHovered())
					cm_itemHighlightedIdx = n;

				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndListBox();
		}

		if (ImGui::Button("Add"))
		{
			switch (cm_itemSelected)
			{
			case 0:
				target->AddComponent<SphereCollider>();
				break;

			case 1:
				target->AddComponent<AABBCollider>();
				break;

			case 2:
				target->AddComponent<PlaneCollider>();
				break;

			default:
				assert(false);
			}

		}
	}
	else
	{
	}
}
