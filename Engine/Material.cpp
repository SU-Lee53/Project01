#include "EnginePch.h"
#include "Material.h"
#include "Shader.h"

Material::Material()
{
}

Material::~Material()
{
}

void Material::SetMaterialData(const MaterialData& data)
{
	_materialData = data;
}

void Material::PushMaterialData()
{
	RENDER->SetMaterialData(_materialData);
}

void Material::SetVertexShader(shared_ptr<VertexShader> shader)
{
	_shader->SetVertexShader(shader);
}

void Material::SetPixelShader(shared_ptr<PixelShader> shader)
{
	_shader->SetPixelShader(shader);
}

void Material::SetShader(shared_ptr<Shader> shader)
{
	_shader = shader;
}
