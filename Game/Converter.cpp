#include "pch.h"
#include "Converter.h"
#include "Model.h"
#include "Material.h"
#include "Texture.h"
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
	//wstring path = L"../Models/car_test/source/silvia_varietta.fbx";
	wstring path = L"../Models/temp/pool.fbx";
	//wstring path = L"../Models/pool_table/pool_table.fbx";	-> Texture loading fail
	//wstring path = L"../Models/balls/source/poolballs.fbx";	-> Too big(1800+ vertices per ball) + PoolStick missing...

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

void Converter::ExportAssetFile()
{

}

void Converter::ExportModel()
{

}

void Converter::ExportMesh()
{

}

void Converter::ExportMaterial()
{

}

wstring GetTextureName(const wstring& origin)
{
	wstring ret = L"";

	auto it = find(origin.rbegin(), origin.rend(), L'\\');
	if (it == origin.rend())
	{
		assert(false);
	}
	else
	{
		ret = wstring(origin.rbegin(), it);
		reverse(ret.begin(), ret.end());
	}

	return ret;
}

shared_ptr<Model> Converter::MakeModel()
{
	// Recycle the code below to export bones/models/materials

	auto model = make_shared<Model>();

	vector<shared_ptr<ModelBone>> modelBones;

	for (const auto asbone : _bones)
	{
		shared_ptr<ModelBone> bone = make_shared<ModelBone>();
		bone->index = asbone->index;
		bone->name = Utils::ToWString(asbone->name);
		bone->parentIndex = asbone->parent;
		bone->transform = asbone->transform;

		modelBones.push_back(bone);
	}
	
	vector<shared_ptr<ModelMesh>> modelMeshes;

	for (const auto asMesh : _meshes)
	{
		shared_ptr<ModelMesh> mesh = make_shared<ModelMesh>();
		mesh->boneIndex = asMesh->boneIndex;
		mesh->materialName = Utils::ToWString(asMesh->materialName);
		mesh->name = Utils::ToWString(asMesh->name);
		mesh->geometry = make_shared<Geometry<VertexType>>();
		mesh->geometry->SetVertices(asMesh->vertices);
		mesh->geometry->SetIndices(asMesh->indices);
		mesh->MakeBuffers();

		uint32 index = 0;
		auto it = find_if(_materials.begin(), _materials.end(),
			[&index, asMesh](auto m) -> bool
			{
				if (m->name == asMesh->materialName)
					return true;
				else
					index++;

				return false;
			}
		);

		if (it == _materials.end()) assert(false);

		mesh->materialIndex = index;
		



		modelMeshes.push_back(mesh);
	}

	vector<shared_ptr<Material>> materials;

	for (const auto asMaterial : _materials)
	{
		shared_ptr<Material> material = make_shared<Material>();

		material->SetName(Utils::ToWString(asMaterial->name));

		MaterialData data;
		{
			data.ambient = asMaterial->ambient;
			data.diffuse = asMaterial->diffuse;
			data.specular = asMaterial->specular;
			data.emissive = asMaterial->emissive;
		}
		material->SetMaterialData(data);
		
		wstring path = L"../Models/temp/";
		//wstring path = L"../Models/pool_table/pool_text/";
		//wstring path = L"../Models/balls/textures/";


		wstring originName;
		wstring fileName;

		{
			// Diffuse
			if(!asMaterial->diffuseFile.empty())
			{
				originName = Utils::ToWString(asMaterial->diffuseFile);
				//fileName = GetTextureName(originName);
				auto diff = make_shared<Texture>();
				diff->Create(path + fileName);
				material->SetDiffuseMap(diff);
			}
			else
			{
				auto err = make_shared<Texture>();
				err->CreateErrorTexture();
				material->SetDiffuseMap(err);
			}

			// Normal
			if (!asMaterial->normalFile.empty())
			{
				originName = Utils::ToWString(asMaterial->normalFile);
				//fileName = GetTextureName(originName);
				auto normal = make_shared<Texture>();
				normal->Create(path + fileName);
				material->SetNormalMap(normal);
			}
			else
			{
				auto err = make_shared<Texture>();
				err->CreateErrorTexture();
				material->SetNormalMap(err);
			}

			// Specular
			if (!asMaterial->specularFile.empty())
			{
				originName = Utils::ToWString(asMaterial->specularFile);
				//fileName = GetTextureName(originName);
				auto specular = make_shared<Texture>();
				specular->Create(path + fileName);
				material->SetSpecularMap(specular);
			}
			else
			{
				auto err = make_shared<Texture>();
				err->CreateErrorTexture();
				material->SetSpecularMap(err);
			}
		}

		materials.push_back(material);
	}

	model->SetBone(modelBones);
	model->SetMesh(modelMeshes);
	model->SetMaterial(materials);

	return model;
}

