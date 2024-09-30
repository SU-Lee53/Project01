#include "EnginePch.h"
#include "MeshRenderer.h"
#include "Shader.h"
#include "Mesh.h"

MeshRenderer::MeshRenderer()
{
}
MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Init_impl()
{
	_shader = make_shared<Shader>();
	_mesh = make_shared<Mesh>();

	_shader->Create();
}

void MeshRenderer::Update_impl()
{
	RENDER->PushToRenderObject(GetOwner());
}

void MeshRenderer::Render()
{
}
