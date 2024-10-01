#pragma once
#include "Component.h"

class Mesh;
class Shader;
class Texture;

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

private:
	shared_ptr<Shader> _shader;
	shared_ptr<Mesh> _mesh;
	shared_ptr<Texture> _texture;

public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::MeshRenderer;
};

