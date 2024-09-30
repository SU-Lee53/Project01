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
	_shader->Create();

	if(_mesh == nullptr) // If _mesh was not set
		_mesh = make_shared<Mesh>();	// set default mesh
}

void MeshRenderer::Update_impl()
{
	RENDER->PushToRenderObject(GetOwner());
}

void MeshRenderer::Render()
{
}
