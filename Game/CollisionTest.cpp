#include "pch.h"
#include "CollisionTest.h"
#include "GameObject.h"
#include "Model.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "MouseScript.h"
#include "ModelScript.h"
#include "LightScript.h"
#include "GlobalLight.h"
#include "BaseCollider.h"
#include "Scene.h"
#include "SceneModelController.h"

#include "Material.h"

void CollisionTest::Init()
{

	for (const auto& targets : LoadTargets)
	{
		auto obj = make_shared<GameObject>();
		{
			obj->AddComponent<Transform>();
			obj->AddComponent<MeshRenderer>();

			auto model = make_shared<Model>();
			model->LoadFromFiles(targets);
			obj->GetComponent<MeshRenderer>()->SetModel(model);

			string name = filesystem::path(targets).filename().string();
			obj->SetName(name);
		}
		CUR_SCENE->AddObject(obj);
	}


	auto _cam = make_shared<GameObject>();
	{
		_cam->AddComponent<Transform>();
		_cam->AddComponent<Camera>();

		_cam->GetComponent<Transform>()->SetPosition(Vec3{ 0.0f, 0.0f, -15.0f });

		auto _mouseScript = make_shared<MouseScript>();
		_cam->AddScript(_mouseScript);

		_cam->SetName("camera");
	}
	CUR_SCENE->AddCamera(_cam);
	CUR_SCENE->SetMainCamera("camera");


	auto _light = make_shared<GameObject>();
	{
		_light->AddComponent<Transform>();
		_light->AddComponent<GlobalLight>();

		GlobalLightData data;
		{
			data.ambient = Vec4(0.5f);
			data.diffuse = Vec4(1.0f);
			data.specular = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
			data.direction = Vec3(0.0f, -1.0f, 1.0f);
		}

		_light->GetComponent<GlobalLight>()->SetData(data);

		auto _lightScript = make_shared<LightScript>();
		_light->AddScript(_lightScript);

		_light->SetName("globalLight");
	}
	CUR_SCENE->AddObject(_light);


	auto sceneScript = make_shared<SceneModelController>();
	CUR_SCENE->AddScript(sceneScript);
}

void CollisionTest::Update()
{
}

void CollisionTest::Render()
{
	CUR_SCENE->Render();
}
