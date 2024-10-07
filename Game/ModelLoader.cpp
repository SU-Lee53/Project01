#include "pch.h"
#include "ModelLoader.h"
#include "Converter.h"
#include "GameObject.h"
#include "Model.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "MouseScript.h"
#include "ModelScript.h"

void ModelLoader::Init()
{
	_converter = make_shared<Converter>();

	_converter->LoadAssetFile();

	{
		auto model = make_shared<Model>();
		model = _converter->MakeModel();
		RESOURCE->Add("Car", model);
	}

	_obj = make_shared<GameObject>();
	{
		_obj->AddComponent<Transform>();
		_obj->AddComponent<MeshRenderer>();
		_obj->Init();

		_obj->GetComponent<MeshRenderer>()->SetModel(RESOURCE->Get<Model>("Car"));

		_mouseScript = make_shared<ModelScript>();
		_obj->AddScript(_mouseScript);
	}

	{
		_cam = make_shared<GameObject>();
		_cam->AddComponent<Transform>();
		_cam->AddComponent<Camera>();
		_cam->Init();

		_cam->GetComponent<Transform>()->SetPosition(Vec3{ 0.0f, 0.0f, -5.0f });

		_mouseScript = make_shared<MouseScript>();
		_cam->AddScript(_mouseScript);
	}


}

void ModelLoader::Update()
{
	{
		ImGui::Begin("Test on TestExe");
		ImGui::Text("MousePos.x : %li", INPUT->GetMousePos().x);
		ImGui::Text("MousePos.y : %li", INPUT->GetMousePos().y);

		auto pos = _cam->GetComponent<Transform>()->GetPosition();
		ImGui::Text("CameraPos.x : %f", pos.x);
		ImGui::Text("CameraPos.y : %f", pos.y);
		ImGui::Text("CameraPos.z : %f", pos.z);

		ImGui::End();
	}

	_obj->Update();
	_cam->Update();
}

void ModelLoader::Render()
{
	RENDER->Render();
}
