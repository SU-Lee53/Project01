#include "EnginePch.h"
#include "ModelTypes.h"

void ModelMesh::MakeBuffers()
{

	vertexBuffer = make_shared<VertexBuffer>();
	vertexBuffer->Create(geometry->GetVertices());

	indexBuffer = make_shared<IndexBuffer>();
	indexBuffer->Create(geometry->GetIndices());
}
