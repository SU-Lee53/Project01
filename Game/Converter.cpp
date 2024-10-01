#include "pch.h"
#include "Converter.h"
#include <filesystem>

Converter::Converter()
{
	_importer = make_shared<Assimp::Importer>();
}

Converter::~Converter()
{
}

void Converter::LoadAssetFile()
{
	// Test
	wstring path = L"../Models/source/pool_table_scene.fbx";

	auto p = filesystem::path(path);
	if (!filesystem::exists(p))
		assert(false);

	_scene = _importer->ReadFile(
		Utils::ToString(path),
		aiProcess_ConvertToLeftHanded |
		aiProcess_Triangulate |
		aiProcess_GenUVCoords |
		aiProcess_GenNormals |
		aiProcess_CalcTangentSpace
	);

	if (_scene == nullptr)
		assert(false);

	ReadModel(*(_scene->mRootNode), -1, -1);
}

void Converter::ReadModel(const aiNode& node, int32 index, int32 parent)
{
	auto bone = make_shared<asBone>();
	bone->index = index;
	bone->parent = parent;
	bone->name = node.mName.C_Str();

	// Relative (from parent)
	Matrix transform(node.mTransformation[0]);
	bone->transform = transform.Transpose();

	// Local (root)
	Matrix matParent = Matrix::Identity;
	if (parent >= 0)
		matParent = _bones[parent]->transform;

	// model -> root;
	bone->transform = bone->transform * matParent;

	_bones.push_back(bone);

	// TODO : Make ReadMesh and Call here

	// Recursive
	for (uint32 i = 0; i < node.mNumChildren; i++)
	{
		ReadModel(*(node.mChildren[i]), _bones.size(), index);
	}
}

