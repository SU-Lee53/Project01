#pragma once
#include "Resource_Base.h"

enum MaterialMask : uint8
{
	HAS_NOTHING = 0,
	HAS_DIFFUSE = 1,
	HAS_SPECULAR = HAS_DIFFUSE << 1,
	HAS_NORMAL = HAS_SPECULAR << 1,
};

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

	MaterialMask GetMaterialAttributes() { return _attributes; }
	void SetMaterialAttributes(MaterialMask m) { _attributes = m; }

public:
	static bool CheckAttributes(MaterialMask target, MaterialMask checker);

public:
	void SetVertexShader(shared_ptr<VertexShader> shader);
	void SetPixelShader(shared_ptr<PixelShader> shader);
	void SetShader(shared_ptr<Shader> shader);
	
	shared_ptr<VertexShader> GetVertexShader();
	shared_ptr<PixelShader> GetPixelShader();
	shared_ptr<Shader> GetShader();

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

public:
	MaterialMask _attributes = HAS_NOTHING;

	using Ty = Material;
};

