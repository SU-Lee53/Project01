#pragma once

struct ModelBone
{
	wstring name;
	uint32 index;
	uint32 parentIndex;
	Matrix transform;
};

struct ModelMesh
{
	void MakeBuffers();

	wstring name;

	shared_ptr<Geometry<VertexType>> geometry;
	shared_ptr<VertexBuffer> vertexBuffer;
	shared_ptr<IndexBuffer> indexBuffer;

	wstring materialName = L"";
	uint32 materialIndex;

	uint32 boneIndex;
};