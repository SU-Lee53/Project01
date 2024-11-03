#include "pch.h"
#include "LightScript.h"
#include "GameObject.h"
#include "GlobalLight.h"

void LightScript::Init()
{
	_lightData = GetOwner()->GetComponent<GlobalLight>()->GetData();
}

void LightScript::Update()
{
	if (ImGui::Begin("Light Controller"))
	{
		if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { _dragSpeed -= 0.05f; }
		ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
		if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { _dragSpeed += 0.05f; }
		ImGui::SameLine();
		ImGui::Text("Drag Speed : %f", _dragSpeed);

		ImGui::InputFloat3("Ambient", (float*)&_lightData.ambient);
		ImGui::DragFloat("Ambient.R", &_lightData.ambient.x, _dragSpeed, 0.f, 1.f);
		ImGui::DragFloat("Ambient.G", &_lightData.ambient.y, _dragSpeed, 0.f, 1.f);
		ImGui::DragFloat("Ambient.B", &_lightData.ambient.z, _dragSpeed, 0.f, 1.f);
		
		ImGui::InputFloat3("Diffuse", (float*)&_lightData.diffuse);
		ImGui::DragFloat("Diffuse.R", &_lightData.diffuse.x, _dragSpeed, 0.f, 1.f);
		ImGui::DragFloat("Diffuse.G", &_lightData.diffuse.y, _dragSpeed, 0.f, 1.f);
		ImGui::DragFloat("Diffuse.B", &_lightData.diffuse.z, _dragSpeed, 0.f, 1.f);
		
		ImGui::InputFloat3("Specular", (float*)&_lightData.specular);
		ImGui::DragFloat("Specular.R", &_lightData.specular.x, _dragSpeed, 0.f, 1.f);
		ImGui::DragFloat("Specular.G", &_lightData.specular.y, _dragSpeed, 0.f, 1.f);
		ImGui::DragFloat("Specular.B", &_lightData.specular.z, _dragSpeed, 0.f, 1.f);
		
		ImGui::InputFloat3("Direction", (float*)&_lightData.direction);
		ImGui::DragFloat("Direction.x", &_lightData.direction.x, _dragSpeed, -1.f, 1.f);
		ImGui::DragFloat("Direction.y", &_lightData.direction.y, _dragSpeed, -1.f, 1.f);
		ImGui::DragFloat("Direction.z", &_lightData.direction.z, _dragSpeed, -1.f, 1.f);

		GetOwner()->GetComponent<GlobalLight>()->SetData(_lightData);
	}
	ImGui::End();
}
