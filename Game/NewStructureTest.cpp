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

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();


}

void NewStructureTest::Update()
{
	if (ImGui::Begin("Shaders"))
	{
		auto vss = RESOURCE->GetVertexShaderSet();
		auto pss = RESOURCE->GetPixelShaderSet();

		if (ImGui::TreeNode("VertexShaders"))
		{
			for (const auto& vs : vss)
			{
				ImGui::BulletText("name : %s", vs->GetName().c_str());
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("PixelShaders"))
		{
			for (const auto& ps : pss)
			{
				ImGui::BulletText("name : %s", ps->GetName().c_str());
			}

			ImGui::TreePop();
		}
	}
	ImGui::End();
}

void NewStructureTest::Render()
{
	RENDER->Render();
}
