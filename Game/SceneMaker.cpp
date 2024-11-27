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

#include "SceneMaker.h"

void SceneMaker::Init()
{
}

void SceneMaker::Update()
{
}

void SceneMaker::Render()
{
	CUR_SCENE->Render();
}
