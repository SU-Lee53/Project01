#include "EnginePch.h"
#include "Material.h"

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
