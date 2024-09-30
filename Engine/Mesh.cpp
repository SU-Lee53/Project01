#include "EnginePch.h"
#include "Mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
}

void Mesh::CreateTestGeometry()
{
	_geometry = make_shared<Geometry<MeshType>>();
	Utils::MakeCubeGeometry(_geometry);
	CreateBuffers();
}

void Mesh::CreateBuffers()
{
	_vertexBuffer = make_shared<VertexBuffer>();
	_vertexBuffer->Create(_geometry->GetVertices());
	
	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());
}
