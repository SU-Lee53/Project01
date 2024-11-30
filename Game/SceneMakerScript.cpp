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


	//for (const auto& targets : LoadTargets)
	//{
	//	auto obj = make_shared<GameObject>();
	//	{
	//		obj->AddComponent<Transform>();
	//		obj->GetComponent<Transform>()->SetPosition(Vec3{ 0.f,0.f,0.f });
	//		obj->GetComponent<Transform>()->SetRotation(Vec3{ 0.f,0.f,0.f });
	//		obj->GetComponent<Transform>()->SetScale(Vec3{ 1.f,1.f,1.f });
	//
	//		obj->AddComponent<MeshRenderer>();
	//		auto model = make_shared<Model>();
	//		model->LoadFromFiles(targets);
	//		obj->GetComponent<MeshRenderer>()->SetModel(model);
	//	}
	//	LoadedObjs.push_back(make_pair(filesystem::path(targets).filename().string(), obj));
	//}

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
						if (selected->GetComponent<Transform>())
						{
							// TODO : Add Modifier
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
							// TODO : Add Modifier
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
