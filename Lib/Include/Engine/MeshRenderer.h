#pragma once
#include "Component.h"

class Mesh;
class Shader;
class Texture;
class Material;
class Model;

class MeshRenderer : public Component<MeshRenderer>
{
public:
	MeshRenderer();
	~MeshRenderer();

public:
	void Init_impl();
	void Update_impl();
	void Render();

public:
	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	shared_ptr<Mesh> GetMesh() const { return _mesh; }

	void SetTexture(shared_ptr<Texture> texture) { _texture = texture; }
	shared_ptr<Texture> GetTexture() const { return _texture; }
	
	void SetMaterial(shared_ptr<Material> material) { _material = material; }
	shared_ptr<Material> GetMaterial() const { return _material; }

	void SetModel(shared_ptr<Model> model) { _model = model; }
	shared_ptr<Model> GetModel() const { return _model; }

private:
	shared_ptr<Shader> _shader;
	shared_ptr<Mesh> _mesh;
	shared_ptr<Texture> _texture;

	shared_ptr<Material> _material;

private:
	shared_ptr<Model> _model;

public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::MeshRenderer;
};

