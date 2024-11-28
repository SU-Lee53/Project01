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
		if (ImGui::BeginTabItem("Shader"))
		{
			ImGui::Text("Vertex Shader");
			ImGui::Text("Name : %s", _shader->GetVertexShader()->GetName().c_str());
			ImGui::Text("Path : %s", Utils::ToString(_shader->GetVertexShader()->GetPath()).c_str());
			

			ImGui::NewLine();  ImGui::Text("Pixel Shader");
			ImGui::Text("Name : %s", _shader->GetPixelShader()->GetName().c_str());
			ImGui::Text("Path : %s", Utils::ToString(_shader->GetPixelShader()->GetPath()).c_str());
			
			ImGui::EndTabItem();
		}

		// useless parts tbh
		{
			if (_mesh)
			{
				if (ImGui::BeginTabItem("Mesh"))
				{
					ImGui::Text("This is useless");
					ImGui::Text("If you watch this, go fix it");
					ImGui::EndTabItem();
				}
			}

			if (_texture)
			{
				if (ImGui::BeginTabItem("Texture"))
				{
					ImGui::Text("This is useless");
					ImGui::Text("If you watch this, go fix it");
					ImGui::EndTabItem();
				}
			}
		}

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
