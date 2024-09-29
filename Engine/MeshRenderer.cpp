#include "EnginePch.h"
#include "MeshRenderer.h"
#include "Mesh.h"

MeshRenderer::MeshRenderer()
{
}
MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Update_impl()
{
	RENDER->PushToRenderObject(GetOwner());
}

void MeshRenderer::Render()
{
}
