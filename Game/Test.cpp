#include "pch.h"
#include "Test.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "TestScript.h"
#include "Script.h"

void Test::Init()
{
	{
		_obj = make_shared<GameObject>();
		_obj->AddComponent<Transform>();
		_obj->AddComponent<MeshRenderer>();
		_obj->Init();

		auto mesh = make_shared<Mesh>();
		mesh->CreateTestGeometry();
		_obj->GetComponent<MeshRenderer>()->SetMesh(mesh);
	}

	{
		_cam = make_shared<GameObject>();
		_cam->AddComponent<Transform>();
		_cam->AddComponent<Camera>();
		_cam->Init();

		_cam->GetComponent<Transform>()->SetPosition(Vec3{ 0.0f, 0.0f, -5.0f });
	}

	_script = make_shared<TestScript>();
	_cam->AddScript(_script);
}

void Test::Update()
{
	{
		_obj->GetComponent<Transform>()->SetRotation(Vec3{ 45.f, temp, 45.f });
		temp += 50.f * DELTA_TIME;
	}

	{
		ImGui::Begin("Test on TestExe");
		ImGui::Text("MousePos.x : %li", INPUT->GetMousePos().x);
		ImGui::Text("MousePos.y : %li", INPUT->GetMousePos().y);
		ImGui::End();
	}

	_obj->Update();
	_cam->Update();
}

void Test::Render()
{
	RENDER->Render();
}
