#include "EnginePch.h"
#include "RenderManager.h"

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::Render(shared_ptr<GameObject>& obj)
{
	if(obj->GetComponent<MeshRenderer>() != nullptr)
	{
		obj->GetComponent<Transform>()->PushTransform();
		obj->GetComponent<MeshRenderer>()->Render();
	}
}
