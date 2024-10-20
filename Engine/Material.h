#pragma once
#include "Resource_Base.h"

class Material : public Resource_Base
{
public:
	Material();
	virtual ~Material();

public:
	void SetMaterialData(const MaterialData& data);
	MaterialData& GetMaterialData() { return _materialData; }

	void PushMaterialData();

	void SetDiffuseMap(shared_ptr<Texture> map) { _diffuseMap = map; }
	void SetNormalMap(shared_ptr<Texture> map) { _normalMap = map; }
	void SetSpecularMap(shared_ptr<Texture> map) { _specularMap = map; }
	
	shared_ptr<Texture> GetDiffuseMap() { return _diffuseMap; }
	shared_ptr<Texture> GetNormalMap() { return _normalMap; }
	shared_ptr<Texture> GetSpecularMap() { return _specularMap; }

	void SetVertexShader(shared_ptr<VertexShader> shader);
	void SetPixelShader(shared_ptr<PixelShader> shader);
	void SetShader(shared_ptr<Shader> shader);

private:
	MaterialData _materialData;

	shared_ptr<Texture> _diffuseMap;
	shared_ptr<Texture> _normalMap;
	shared_ptr<Texture> _specularMap;

private:
	shared_ptr<Shader> _shader;

public:
	static const int32 _diffuseSlot = 0; 
	static const int32 _normalSlot = 1;
	static const int32 _specularSlot = 2;

	using Ty = Material;
};

