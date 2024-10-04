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
	wstring path = L"../Models/source/poolballs.fbx";

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
	ReadMaterial();
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
	ReadMesh(node, index);

	// Recursive
	for (uint32 i = 0; i < node.mNumChildren; i++)
	{
		ReadModel(*(node.mChildren[i]), _bones.size(), index);
	}
}

void Converter::ReadMesh(const aiNode& node, int32 bone)
{
	if (node.mNumMeshes < 1)
		return;

	shared_ptr<asMesh> mesh = make_shared<asMesh>();
	mesh->name = node.mName.C_Str();
	mesh->boneIndex = bone;

	for (uint32 i = 0; i < node.mNumMeshes; i++)
	{
		uint32 index = node.mMeshes[i];
		const aiMesh* srcMesh = _scene->mMeshes[index];

		// Material Name
		const aiMaterial* material = _scene->mMaterials[srcMesh->mMaterialIndex];
		mesh->materialName = material->GetName().C_Str();

		const uint32 startVertex = mesh->vertices.size();

		for (uint32 v = 0; v < srcMesh->mNumVertices; v++)
		{
			// Vertex
			VertexType vertex;
			memcpy(&vertex.position, &srcMesh->mVertices[v], sizeof(Vec3));

			// UV
			if (srcMesh->HasTextureCoords(0))
				memcpy(&vertex.uv, &srcMesh->mTextureCoords[0][v], sizeof(Vec2));

			// Normal
			//	if (srcMesh->HasNormals())
			//		memcpy(&vertex.normal, &srcMesh->mNormals[v], sizeof(Vec3));

			// Tangent
			//	if (srcMesh->HasTangentsAndBitangents())
			//		memcpy(&vertex.tangent, &srcMesh->mTangents[v], sizeof(Vec3));

			mesh->vertices.push_back(vertex);
		}

		for (uint32 f = 0; f < srcMesh->mNumFaces; f++)
		{
			aiFace& face = srcMesh->mFaces[f];

			for (uint32 k = 0; k < face.mNumIndices; k++)
				mesh->indices.push_back(face.mIndices[k] + startVertex);
		}
	}
	
	_meshes.push_back(mesh);
}

void Converter::ReadMaterial()
{
	for (uint32 i = 0; i < _scene->mNumMaterials; i++)
	{
		aiMaterial* srcMaterial = _scene->mMaterials[i];

		shared_ptr<asMaterial> material = make_shared<asMaterial>();
		material->name = srcMaterial->GetName().C_Str();

		aiColor3D color;
		aiString file;

		// Ambient
		{
			srcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
			material->ambient = Color(color.r, color.g, color.b, 1.0f);
		}
		
		// Diffuse
		{
			srcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
			material->diffuse = Color(color.r, color.g, color.b, 1.0f);

			srcMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);
			material->diffuseFile = file.C_Str();
		}
		
		// Specular
		{
			srcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
			material->specular = Color(color.r, color.g, color.b, 1.0f);

			srcMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);
			material->specularFile = file.C_Str();
		}
		
		// Emmisive
		{
			srcMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);
			material->emissive = Color(color.r, color.g, color.b, 1.0f);
		}

		// Normal
		{
			srcMaterial->GetTexture(aiTextureType_NORMALS, 0, &file);
			material->normalFile = file.C_Str();
		}

		_materials.push_back(material);
	}
}

