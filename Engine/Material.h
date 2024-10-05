#pragma once
#include "Resource_Base.h"

class Material : public Resource_Base
{
public:
	Material();
	virtual ~Material();

public:
	void SetMaterialData(const MaterialData& data) { _materialData = data; }
	MaterialData& GetMaterialData() { return _materialData; }

	void SetDiffuseMap(shared_ptr<Texture> map) { _diffuseMap = map; }
	void SetNormalMap(shared_ptr<Texture> map) { _normalMap = map; }
	void SetSpecularMap(shared_ptr<Texture> map) { _specularMap = map; }
	
	shared_ptr<Texture> GetDiffuseMap() { return _diffuseMap; }
	shared_ptr<Texture> GetNormalMap() { return _normalMap; }
	shared_ptr<Texture> GetSpecularMap() { return _specularMap; }

private:
	MaterialData _materialData;

	shared_ptr<Texture> _diffuseMap;
	shared_ptr<Texture> _normalMap;
	shared_ptr<Texture> _specularMap;

public:
	static const int32 _diffuseSlot = 0; 
	static const int32 _normalSlot = 1;
	static const int32 _specularSlot = 2;

	using Ty = Material;
};

