#pragma once
#include "Component.h"

class MeshRenderer : public Component<MeshRenderer>
{
public:
	MeshRenderer();
	~MeshRenderer();

public:
	void Update_impl();
	void Render();

public:
	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }

private:
	shared_ptr<Mesh> _mesh;

public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::MeshRenderer;
};

