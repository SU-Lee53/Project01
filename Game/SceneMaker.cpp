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
#include "SceneMaker.h"
#include "GlobalLight.h"
#include "BaseCollider.h"
#include "Scene.h"
#include "SceneModelController.h"
#include "SceneMakerScript.h"

void SceneMaker::Init()
{
	auto testObj = make_shared<GameObject>();
	{
		testObj->AddComponent<Transform>();
		testObj->AddComponent<MeshRenderer>();
		testObj->AddComponent<SphereCollider>();

		auto m = make_shared<Model>();
		m->LoadFromFiles(L"pool_ball_7.mesh");
		testObj->AddComponent<MeshRenderer>();
		testObj->GetComponent<MeshRenderer>()->SetModel(m);

		testObj->GetComponent<Transform>()->SetScale(Vec3(0.1f, 0.1f, 0.1f));

		testObj->SetName("testObj");
	}
	CUR_SCENE->AddObject(testObj);

	auto testObj2 = make_shared<GameObject>();
	{
		testObj2->AddComponent<Transform>();
		testObj2->AddComponent<MeshRenderer>();
		testObj2->AddComponent<SphereCollider>();

		auto m = make_shared<Model>();
		m->LoadFromFiles(L"pool_ball_9.mesh");
		testObj2->AddComponent<MeshRenderer>();
		testObj2->GetComponent<MeshRenderer>()->SetModel(m);

		testObj2->GetComponent<Transform>()->SetPosition(Vec3(15.f, 0.f, 0.f));
		testObj2->GetComponent<Transform>()->SetScale(Vec3(0.1f, 0.1f, 0.1f));
		//testObj2->GetComponent<Transform>()->SetScale(Vec3(0.1f, 0.1f, 0.1f));

		testObj2->SetName("testObj2");
	}
	CUR_SCENE->AddObject(testObj2);
	
	auto testObj3 = make_shared<GameObject>();
	{
		testObj3->AddComponent<Transform>();
		testObj3->AddComponent<MeshRenderer>();
		testObj3->AddComponent<SphereCollider>();

		auto m = make_shared<Model>();
		m->LoadFromFiles(L"pool_objectball.mesh");
		testObj3->AddComponent<MeshRenderer>();
		testObj3->GetComponent<MeshRenderer>()->SetModel(m);

		testObj3->GetComponent<Transform>()->SetPosition(Vec3(30.f, 0.f, 0.f));
		testObj3->GetComponent<Transform>()->SetScale(Vec3(0.1f, 0.1f, 0.1f));
		//testObj2->GetComponent<Transform>()->SetScale(Vec3(0.1f, 0.1f, 0.1f));

		testObj3->SetName("testObj3");
	}
	CUR_SCENE->AddObject(testObj3);

	auto testObj4 = make_shared<GameObject>();
	{
		testObj4->AddComponent<Transform>();
		testObj4->AddComponent<MeshRenderer>();
		testObj4->AddComponent<OBBCollider>();

		auto m = make_shared<Model>();
		m->LoadFromFiles(L"pool_cue.mesh");
		testObj4->GetComponent<MeshRenderer>()->SetModel(m);

		testObj4->GetComponent<Transform>()->SetPosition(Vec3(-15.f, 0.f, 0.f));
		testObj4->GetComponent<Transform>()->SetScale(Vec3(1.f, 1.f, 0.25f));
		
		testObj4->SetName("Cue");

	}
	CUR_SCENE->AddObject(testObj4);

	CUR_SCENE->AddCollisionSet(make_pair(testObj->GetCollider(), testObj2->GetCollider()));
	CUR_SCENE->AddCollisionSet(make_pair(testObj2->GetCollider(), testObj3->GetCollider()));
	CUR_SCENE->AddCollisionSet(make_pair(testObj->GetCollider(), testObj3->GetCollider()));
	CUR_SCENE->AddCollisionSet(make_pair(testObj3->GetCollider(), testObj2->GetCollider()));
	CUR_SCENE->AddCollisionSet(make_pair(testObj4->GetCollider(), testObj->GetCollider()));
	CUR_SCENE->AddCollisionSet(make_pair(testObj4->GetCollider(), testObj2->GetCollider()));
	CUR_SCENE->AddCollisionSet(make_pair(testObj4->GetCollider(), testObj3->GetCollider()));


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
		_light->SetName("globalLight");
	}
	CUR_SCENE->SetGlobalLight(_light);

	auto s = make_shared <SceneMakerScript>();
	CUR_SCENE->AddScript(s);
}

void SceneMaker::Update()
{
}

void SceneMaker::Render()
{
	CUR_SCENE->Render();
}
