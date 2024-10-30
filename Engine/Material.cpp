#include "EnginePch.h"
#include "Material.h"
#include "Shader.h"

Material::Material()
{
	// For Test
	_shader = make_shared<Shader>();
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

bool Material::CheckAttributes(MaterialFlag target, MaterialFlag checker)
{
	if (checker == HAS_NOTHING)
	{
		uint8 check = target & HAS_DIFFUSE;
		if (check == HAS_DIFFUSE)
		{
			return false;
		}
		return true;
	}
	else
	{
		uint8 check = target & checker;

		if (check == checker)
		{
			return true;
		}
		return false;
	}

	assert(false);
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

shared_ptr<VertexShader> Material::GetVertexShader()
{
	return _shader->GetVertexShader(); 
}

shared_ptr<PixelShader> Material::GetPixelShader()
{
	return _shader->GetPixelShader();
}

shared_ptr<Shader> Material::GetShader()
{
	return _shader;
}
