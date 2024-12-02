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

			// Component Selector flags
			const uint8 CP_TRANSFORM = 1;
			const uint8 CP_MESHRENDERER = CP_TRANSFORM << 1;

			ImGui::InputText("Name", cam_name, IM_ARRAYSIZE(cam_name));
			if (ImGui::Button("Add to Scene"))
			{
				shared_ptr<GameObject> add = make_shared<GameObject>();
				add->SetName(cam_name);
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
						if (selected->GetComponent<Transform>())
						{
							selected->GetComponent<Transform>()->ShowStatusToImGui();
						}
						else
						{
							ImGui::Text("No Transform");
						}
						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("MeshRenderer"))
					{
						ImGui::Text("MeshRenderer");
						if (selected->GetComponent<MeshRenderer>())
						{
							selected->GetComponent<MeshRenderer>()->ShowStatusToImGui();
						}
						else
						{
							ImGui::Text("No MeshRenderer");
						}

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("GlobalLight"))
					{
						ImGui::Text("GlobalLight");
						if (selected->GetComponent<GlobalLight>())
						{
							// TODO : Add inspector
							selected->GetComponent<GlobalLight>()->ShowStatusToImGui();
						}
						else
						{
							ImGui::Text("No GlobalLight");
						}

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Collider"))
					{
						ImGui::Text("Collider");
						ImGui::Text("TODO : Complete collider first!!!!!!!");

						ImGui::EndTabItem();
					}


					ImGui::EndTabBar();
				}
			}

			ImGui::EndTabItem();
		}

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
			ImGui::InputText("Name", cam_name, IM_ARRAYSIZE(cam_name));
			ImGui::InputFloat3("Pos", (float*)& cam_pos);

			if (ImGui::Button("Add new camera"))
			{
				shared_ptr<GameObject> add = make_shared<GameObject>();
				add->AddComponent<Transform>();
				add->GetComponent<Transform>()->SetPosition(cam_pos);
				add->AddComponent<Camera>();

				auto _mouseScript = make_shared<MouseScript>();
				add->AddScript(_mouseScript);

				add->SetName(cam_name);
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



		ImGui::EndTabBar();
	}


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

			ImGui::InputText("Name", cam_name, IM_ARRAYSIZE(cam_name));
			ImGui::SameLine();
			if (ImGui::Button("Add to Scene"))
			{
				shared_ptr<GameObject> add = make_shared<GameObject>();
				add->SetName(cam_name);
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

					if (ImGui::BeginTabItem("GlobalLight"))
					{
						ImGui::Text("GlobalLight");
						if (selected->GetComponent<GlobalLight>())
						{
							// TODO : Add Modifier
						}
						else
						{
							ImGui::Text("No GlobalLight");
						}

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Collider"))
					{
						ImGui::Text("Collider");
						ImGui::Text("TODO : Complete collider first!!!!!!!");

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

void SceneMakerScript::UpdateComboList()
{
	LoadedObjs.clear();

	unordered_set<shared_ptr<GameObject>> objSet = GetOwner()->GetObjects();
	for (const auto& obj : objSet)
	{
		LoadedObjs.push_back(make_pair(obj->GetName(), obj));
	}

	lo_prevComboListSize = LoadedObjs.size();
}
