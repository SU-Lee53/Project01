#pragma once
#include "Resource_Base.h"
#include "InputData.h"
#include "Geometry.h"

class Mesh : public Resource_Base
{
public:
	Mesh();
	virtual ~Mesh();

	void CreateTestGeometry();

	shared_ptr<VertexBuffer> GetVertexBuffer() const { return _vertexBuffer; }
	shared_ptr<IndexBuffer> GetIndexBuffer() const { return _indexBuffer; }

	void CreateBuffers();

private:
	shared_ptr<Geometry<VertexType>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

public:
	using Ty = Mesh;
};

