#include "EnginePch.h"
#include "RenderManager.h"
#include "GameObject.h"

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::Update()
{
	_renderObj.clear();
}

void RenderManager::Render()
{
	for (const auto& o : _renderObj)
	{
		o->GetComponent<Transform>()->PushTransform();
		o->GetComponent<MeshRenderer>()->Render();
	}
}
