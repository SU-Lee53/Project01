#pragma once
#include "Utils.h"

struct ModelBone
{
	wstring name = L"";
	uint32 index = -1;
	uint32 parentIndex = -1;
	Matrix transform = Matrix::Identity;

};

struct ModelMesh
{
	void MakeBuffers();

	wstring name = L"";

	shared_ptr<Geometry<VertexType>> geometry;
	shared_ptr<VertexBuffer> vertexBuffer;
	shared_ptr<IndexBuffer> indexBuffer;

	wstring materialName = L"";
	uint32 materialIndex = -1;

	uint32 boneIndex = -1;
};