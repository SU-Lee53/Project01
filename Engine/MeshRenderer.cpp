#include "EnginePch.h"
#include "MeshRenderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "Texture.h"

MeshRenderer::MeshRenderer()
{
}
MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Init_impl()
{
	_shader = make_shared<Shader>();
	_shader->CreateDefault();
}

void MeshRenderer::Update_impl()
{
	if(_model)
		RENDER->PushToRenderObject(GetOwner());
}

void MeshRenderer::Render()
{
}

void MeshRenderer::ShowStatusToImGui()
{
	// Show what?
	//	- _shader
	//	- if _mesh
	//	- if _texture
	//	- if _model

	if (ImGui::BeginTabBar("MeshRenderer"))
	{
		if (_model)
		{
			if (ImGui::BeginTabItem("Model"))
			{
				_model->ShowModelHierarchy();
				ImGui::EndTabItem();
			}
		}


		ImGui::EndTabBar();
	}
	// show shader


}
