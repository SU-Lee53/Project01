#include "pch.h"
#include "NewStructureTest.h"
#include "Converter.h"
#include "GameObject.h"
#include "Model.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "MouseScript.h"
#include "ModelScript.h"
#include "LightScript.h"
#include "GlobalLight.h"
#include <filesystem>

void NewStructureTest::Init()
{
	_obj = make_shared<GameObject>();
	{
		_obj->AddComponent<Transform>();
		_obj->AddComponent<MeshRenderer>();
		_obj->Init();

		auto model = make_shared<Model>();
		model->LoadFromFiles(L"floor.mesh");
		_obj->GetComponent<MeshRenderer>()->SetModel(model);

	}

	_obj2 = make_shared<GameObject>();
	{
		_obj2->AddComponent<Transform>();
		_obj2->AddComponent<MeshRenderer>();
		_obj2->Init();

		auto model = make_shared<Model>();
		model->LoadFromFiles(L"pool_ball_1.mesh");
		_obj2->GetComponent<MeshRenderer>()->SetModel(model);

	}

	_cam = make_shared<GameObject>();
	{
		_cam->AddComponent<Transform>();
		_cam->AddComponent<Camera>();
		_cam->Init();

		_cam->GetComponent<Transform>()->SetPosition(Vec3{ 0.0f, 0.0f, -5.0f });

		_mouseScript = make_shared<MouseScript>();
		_cam->AddScript(_mouseScript);
	}


	_light = make_shared<GameObject>();
	{
		_light->AddComponent<Transform>();
		_light->AddComponent<GlobalLight>();
		_light->Init();

		GlobalLightData data;
		{
			data.ambient = Vec4(0.5f);
			data.diffuse = Vec4(1.0f);
			data.specular = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
			data.direction = Vec3(0.0f, -1.0f, 0.0f);
		}

		_light->GetComponent<GlobalLight>()->SetData(data);

		_lightScript = make_shared<LightScript>();
		_light->AddScript(_lightScript);
	}

}

void NewStructureTest::Update()
{
	if (ImGui::Begin("Shaders"))
	{
		auto vss = SHADER->GetVertexShaderSet();
		auto pss = SHADER->GetPixelShaderSet();

		if (ImGui::TreeNode("VertexShaders"))
		{
			for (const auto& vs : vss)
			{
				auto name = filesystem::path(vs->GetPath()).filename().string();
				ImGui::BulletText("name : %s", name.c_str());
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("PixelShaders"))
		{
			for (const auto& ps : pss)
			{
				auto name = filesystem::path(ps->GetPath()).filename().string();
				ImGui::BulletText("name : %s", name.c_str());
			}

			ImGui::TreePop();
		}
	}
	ImGui::End();


	_obj->Update();
	_obj2->Update();
	_light->Update();
	_cam->Update();


}

void NewStructureTest::Render()
{
	RENDER->Render();
}
