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
}

void MeshRenderer::Render()
{
	//glUseProgram(RENDER->GetShader()->GetID());
	//glBindVertexArray(_mesh->GetVAO()->GetID());
	//
	//glDrawElements(
	//	GL_TRIANGLES,
	//	_mesh->GetVAO()->GetVBO<BUFFER_TYPE::Index>().GetBufferData().size(),
	//	GL_UNSIGNED_INT,
	//	0
	//);
}
