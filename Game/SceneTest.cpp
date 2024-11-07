#include "pch.h"
#include "SceneTest.h"
#include "GameObject.h"
#include "Model.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "MouseScript.h"
#include "ModelScript.h"
#include "LightScript.h"
#include "GlobalLight.h"
#include "Scene.h"

void SceneTest::Init()
{
	auto _obj = make_shared<GameObject>();
	{
		_obj->AddComponent<Transform>();
		_obj->AddComponent<MeshRenderer>();
		_obj->Init();

		auto model = make_shared<Model>();
		model->LoadFromFiles(L"floor.mesh");
		_obj->GetComponent<MeshRenderer>()->SetModel(model);
	}
	CUR_SCENE->AddObject(_obj);

	auto _obj2 = make_shared<GameObject>();
	{
		_obj2->AddComponent<Transform>();
		_obj2->AddComponent<MeshRenderer>();
		_obj2->Init();

		auto model = make_shared<Model>();
		model->LoadFromFiles(L"pool_ball_1.mesh");
		_obj2->GetComponent<MeshRenderer>()->SetModel(model);

	}
	CUR_SCENE->AddObject(_obj2);

	auto _cam = make_shared<GameObject>();
	{
		_cam->AddComponent<Transform>();
		_cam->AddComponent<Camera>();
		_cam->Init();

		_cam->GetComponent<Transform>()->SetPosition(Vec3{ 0.0f, 0.0f, -5.0f });

		auto _mouseScript = make_shared<MouseScript>();
		_cam->AddScript(_mouseScript);
	}
	CUR_SCENE->AddCamera("main_cam", _cam);
	CUR_SCENE->SetMainCamera("main_cam");


	auto _light = make_shared<GameObject>();
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

		auto _lightScript = make_shared<LightScript>();
		_light->AddScript(_lightScript);
	}
	CUR_SCENE->AddObject(_light);

}

void SceneTest::Update()
{
}

void SceneTest::Render()
{
	CUR_SCENE->Render();
}
