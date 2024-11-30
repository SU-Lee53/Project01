#include "EnginePch.h"
#include "GlobalLight.h"

GlobalLight::GlobalLight()
{
}

GlobalLight::~GlobalLight()
{
}

void GlobalLight::Init_impl()
{
}

void GlobalLight::Update_impl()
{
	PushData();
}

void GlobalLight::SetData(const GlobalLightData& data)
{
	_data = data;
}

void GlobalLight::PushData()
{
	RENDER->SetGlobalLightData(_data);
}

void GlobalLight::ShowStatusToImGui()
{
	ImGui::NewLine();
	ImGui::Text("Ambient");
	ImGui::Text("(r, g, b, a) : (%3f, %3f, %3f, %3f)", _data.ambient.x, _data.ambient.y, _data.ambient.z, _data.ambient.w);

	ImGui::NewLine();
	ImGui::Text("Diffuse");
	ImGui::Text("(r, g, b, a) : (%3f, %3f, %3f, %3f)", _data.diffuse.x, _data.diffuse.y, _data.diffuse.z, _data.diffuse.w);

	ImGui::NewLine();
	ImGui::Text("Specular");
	ImGui::Text("(r, g, b, a) : (%3f, %3f, %3f, %3f)", _data.specular.x, _data.specular.y, _data.specular.z, _data.specular.w);
	
	ImGui::NewLine();
	ImGui::Text("Emissive");
	ImGui::Text("(r, g, b, a) : (%3f, %3f, %3f, %3f)", _data.emissive.x, _data.emissive.y, _data.emissive.z, _data.emissive.w);

	ImGui::NewLine();
	ImGui::Text("Direction");
	ImGui::Text("(x, y, z) : (%3f, %3f, %3f)", _data.direction.x, _data.direction.y, _data.direction.z);

}
