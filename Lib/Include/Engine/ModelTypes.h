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
	wstring name;

	shared_ptr<Geometry<VertexType>> geometry;
	shared_ptr<VertexBuffer> vertexBuffer;
	shared_ptr<IndexBuffer> IndexBuffer;

	wstring materialName = L"";
	uint32 boneIndex;
};