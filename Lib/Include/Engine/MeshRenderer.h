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
	virtual ~MeshRenderer();

public:
	void Init_impl();
	void Update_impl();
	void Render();

public:
	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	shared_ptr<Mesh> GetMesh() const { return _mesh; }

	void SetTexture(shared_ptr<Texture> texture) { _texture = texture; }
	shared_ptr<Texture> GetTexture() const { return _texture; }

	void SetModel(shared_ptr<Model> model) { _model = model; }
	shared_ptr<Model> GetModel() const { return _model; }

private:
	shared_ptr<Shader> _shader = nullptr;
	shared_ptr<Mesh> _mesh = nullptr;
	shared_ptr<Texture> _texture = nullptr;

public:
	void ShowStatusToImGui();


private:
	shared_ptr<Model> _model = nullptr;

public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::MeshRenderer;
};

