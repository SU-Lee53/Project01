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
	wstring path = L"../Models/temp/pool.fbx";

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

void Converter::LoadAssetFile(const wstring& modelPath, const wstring& texturePath)
{
	_modelPath = modelPath;
	_materialPath = texturePath;

	auto p = filesystem::path(_modelPath);
	if (!filesystem::exists(p))
		assert(false);
	
	auto p2 = filesystem::path(_materialPath);
	if (!filesystem::exists(p2))
		assert(false);

	_scene = _importer->ReadFile(
		Utils::ToString(_modelPath),
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
			if (srcMesh->HasNormals())
				memcpy(&vertex.normal, &srcMesh->mNormals[v], sizeof(Vec3));

			// Tangent
			if (srcMesh->HasTangentsAndBitangents())
				memcpy(&vertex.tangent, &srcMesh->mTangents[v], sizeof(Vec3));

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
		aiReturn res;
		uint8 attributes = 0;

		// Ambient
		{
			res = srcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
			if(res == AI_SUCCESS)
				material->ambient = Color(color.r, color.g, color.b, 1.0f);
			else
				material->ambient = Color(0.f, 0.f, 0.f, 1.0f);
		}
		
		// Diffuse
		{
			res = srcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
			if (res == AI_SUCCESS)
				material->diffuse = Color(color.r, color.g, color.b, 1.0f);
			else
				material->diffuse = Color(0.f, 0.f, 0.f, 1.0f);

			res = srcMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);
			if (res == AI_SUCCESS)
			{
				material->diffuseFile = file.C_Str();
				attributes |= HAS_DIFFUSE;
			}
			else
				material->diffuseFile = "None";
		}
		
		// Specular
		{
			res = srcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
			if (res == AI_SUCCESS)
				material->specular = Color(color.r, color.g, color.b, 1.0f);
			else
				material->specular = Color(0.f, 0.f, 0.f, 1.0f);

			res = srcMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);
			if (res == AI_SUCCESS)
			{
				material->specularFile = file.C_Str();
				attributes |= HAS_SPECULAR;
			}
			else
				material->specularFile = "None";
		}
		
		// Emmisive
		{
			res = srcMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);
			if (res == AI_SUCCESS)
				material->emissive = Color(color.r, color.g, color.b, 1.0f);
			else
				material->emissive = Color(0.f, 0.f, 0.f, 1.0f);
		}

		// Normal
		{
			res = srcMaterial->GetTexture(aiTextureType_NORMALS, 0, &file);
			if (res == AI_SUCCESS)
			{
				material->normalFile = file.C_Str();
				attributes |= HAS_NORMAL;
			}
			else
				material->normalFile = "None";
		}

		material->attributes = (MaterialMask)attributes;

		_materials.push_back(material);
	}
}

void Converter::Reset()
{
	_bones.clear();
	_meshes.clear();
	_materials.clear();
}

void Converter::ExportAssetFile(wstring name)
{
	ExportModel(name);
}

void Converter::ExportModel(wstring name)
{
	for (auto& mesh : _meshes)
	{
		// save?
		// 1. name
		// 2. vertices, indices
		// 3. bone index
		// 4. material name

		wstring path = _modelExportPath + Utils::ToWString(mesh->name) + L".mesh";
		auto savePath = filesystem::path(path);
		filesystem::create_directory(savePath.parent_path());

		ofstream os(savePath, ios::ate | ios::binary);
		if (!os.is_open())
			assert(false, "Failed to Open");

		if (os.fail())
			assert(false, "ostream failed");

		os << ios::binary;

		os << "names begin" << '\n';
		os << mesh->name << '\n';
		os << mesh->materialName << '\n';
		os << "names end" << '\n';

		os << "vertices begin" << '\n';
		for (const auto& v : mesh->vertices)
		{
			os << v.position.x << ' ' << v.position.y << ' ' << v.position.z << '\n';
			os << v.uv.x << ' ' << v.uv.y << '\n';
			os << v.normal.x << ' ' << v.normal.y << ' ' << v.normal.z << '\n';
			os << v.tangent.x << ' ' << v.tangent.y << ' ' << v.tangent.z << '\n';
		}
		os << "vertices end" << '\n';

		os << "indices begin" << '\n';
		for (const auto& i : mesh->indices)
		{
			os << i << '\n';
		}
		os << "indices end" << '\n';

		ParseBonesByMeshAndExport(os, mesh);
		ExportMaterialsByMesh(os, mesh, _materialExportPath);
	}
}

void Converter::ParseBonesByMeshAndExport(ofstream& os, shared_ptr<asMesh> mesh)
{
	if (!os.is_open())
		assert(false, "Failed to Open");

	if (os.fail())
		assert(false, "ostream failed");

	int32 findKey = mesh->boneIndex;
	auto finder =
		[&findKey](shared_ptr<asBone> bone)->bool
		{
			if (bone->index == findKey)
				return true;
			else
				return false;
		};

	vector<asBone> save;
	auto it = find_if(_bones.begin(), _bones.end(), finder);
	if (it == _bones.end())
		assert(false, "Something wrong while exporting bones");

	while (findKey != -1)
	{
		save.push_back(**it);
		findKey = (*it)->parent;
		it = find_if(_bones.begin(), _bones.end(), finder);
	}
	// add last root bone
	save.push_back(**find_if(_bones.begin(), _bones.end(), finder));

	// reverses (for convenient)
	reverse(save.begin(), save.end());

	// sync real index to bone index + match parent index
	for (int32 i = 0; i < save.size(); i++)
	{
		asBone& b = save[i];
		int32 originIndex = b.index;

		for_each(save.begin(), save.end(),
			[&i, &originIndex](asBone& bone)
			{
				if (bone.parent == originIndex)
					bone.parent = i;
			}
		);

		b.index = i;
	}

	// Now, time for export bones
	os << "bones begin" << '\n';
	os << save.back().index << '\n'; // mesh's boneIndex
	for (const auto& b : save)
	{
		os << b.name << '\n';
		os << b.index << '\n';
		os << b.parent << '\n';
		Utils::ExportMatrix(os, b.transform);
	}
	os << "bones end" << '\n';
}

void Converter::ExportMaterialsByMesh(ofstream& os, shared_ptr<asMesh> mesh, wstring textureSaveFolder)
{
	if (!os.is_open())
		assert(false, "Failed to Open");

	if (os.fail())
		assert(false, "ostream failed");

	string finder = mesh->materialName;
	auto it = find_if(_materials.begin(), _materials.end(),
		[&finder](shared_ptr<asMaterial> material)-> bool
		{
			if (material->name == finder)
				return true;
			return false;
		}
	);

	auto save = *it;

	// Texture save path
	filesystem::path p = filesystem::path(textureSaveFolder + L"Texture/" + Utils::ToWString(mesh->name));
	wstring pathstr = p.c_str();

	// Save
	os << "materials begin" << '\n';
	os << mesh->materialName << '\n';
	
	{
		// Colors
		os << save->diffuse.x << ' ' << save->diffuse.y << ' ' << save->diffuse.z << ' ' << save->diffuse.w << '\n';
		os << save->specular.x << ' ' << save->specular.y << ' ' << save->specular.z << ' ' << save->specular.w << '\n';
		os << save->ambient.x << ' ' << save->ambient.y << ' ' << save->ambient.z << ' ' << save->ambient.w << '\n';
		os << save->emissive.x << ' ' << save->emissive.y << ' ' << save->emissive.z << ' ' << save->emissive.w << '\n';
		
		// Textures
		if (Material::CheckAttributes(save->attributes, HAS_DIFFUSE))
		{
			os << save->diffuseFile << '\n';
			ExportTexture(pathstr, Utils::ToWString(save->diffuseFile));
		}
		else
		{
			os << "None" << '\n';
		}

		if (Material::CheckAttributes(save->attributes, HAS_SPECULAR))
		{
			os << save->specularFile << '\n';
			ExportTexture(pathstr, Utils::ToWString(save->specularFile));
		}
		else
		{
			os << "None" << '\n';
		}

		if (Material::CheckAttributes(save->attributes, HAS_NORMAL))
		{
			os << save->normalFile << '\n';
			ExportTexture(pathstr, Utils::ToWString(save->normalFile));
		}
		else
		{
			os << "None" << '\n';
		}
	}
	os << "materials end" << '\n';

}

void Converter::ExportTexture(wstring textureSavePath, wstring file)
{
	// copy from origin path to my resource path
	string fileName = filesystem::path(file).filename().string();
	string saveFolder = filesystem::path(textureSavePath).filename().string();

	auto findIn = filesystem::path(_materialPath);


}

wstring GetTextureName(const wstring& origin)
{
	wstring ret = L"";

	auto it = find(origin.rbegin(), origin.rend(), L'\\');
	if (it == origin.rend())
	{
		return wstring(origin.cbegin(), origin.cend());
		//assert(false);
	}
	else
	{
		ret = wstring(origin.rbegin(), it);
		reverse(ret.begin(), ret.end());
	}

	return ret;
}

void Converter::ShowMaterials()
{
	if (ImGui::Begin("_converter materials"))
	{
		for (const auto& m : _materials)
		{
			if (ImGui::TreeNode(m->name.c_str()))
			{
				ImGui::BulletText(
					"ambient : R. %.3f G. %.3f B. %.3f A. %.3f\n"
					"diffuse : R. %.3f G. %.3f B. %.3f A. %.3f\n"
					"specular : R. %.3f G. %.3f B. %.3f A. %.3f\n"
					"emissive : R. %.3f G. %.3f B. %.3f A. %.3f\n"
					"diffuseFile : %s\n"
					"specularFile : %s\n"
					"normalFile : %s\n",
					m->ambient.x, m->ambient.y, m->ambient.z, m->ambient.w,
					m->diffuse.x, m->diffuse.y, m->diffuse.z, m->diffuse.w,
					m->specular.x, m->specular.y, m->specular.z, m->specular.w,
					m->emissive.x, m->emissive.y, m->emissive.z, m->emissive.w,
					m->diffuseFile.c_str(),
					m->specularFile.c_str(),
					m->specularFile.c_str()
				);
				ImGui::TreePop();
			}
		}
	}
	ImGui::End();
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
		
		//wstring path = L"../Models/pool_table/pool_text/";
		//wstring path = L"../Models/balls/textures/";

		wstring originName;
		wstring fileName;
		wstring finalPath;

		{
			// Diffuse
			if(!asMaterial->diffuseFile.empty())
			{
				originName = Utils::ToWString(asMaterial->diffuseFile);
				fileName = GetTextureName(originName);
				auto diff = make_shared<Texture>();
				finalPath = _materialPath + fileName;
				diff->Create(finalPath);
				material->SetDiffuseMap(diff);
				material->GetDiffuseMap()->SetName(fileName);
				material->GetDiffuseMap()->SetPath(finalPath);
			}
			else
			{
				auto err = make_shared<Texture>();
				err->CreateErrorTexture();
				material->SetDiffuseMap(err);
				material->GetDiffuseMap()->SetName(fileName);
				material->GetDiffuseMap()->SetPath(finalPath);
			}

			// Normal
			if (!asMaterial->normalFile.empty())
			{
				originName = Utils::ToWString(asMaterial->normalFile);
				fileName = GetTextureName(originName);
				finalPath = _materialPath + fileName;
				auto normal = make_shared<Texture>();
				normal->Create(finalPath);
				material->SetNormalMap(normal);
				material->GetNormalMap()->SetName(fileName);
				material->GetNormalMap()->SetPath(finalPath);
			}
			else
			{
				auto err = make_shared<Texture>();
				err->CreateErrorTexture();
				material->SetNormalMap(err);
				material->GetNormalMap()->SetName(fileName);
				material->GetNormalMap()->SetPath(finalPath);
			}

			// Specular
			if (!asMaterial->specularFile.empty())
			{
				originName = Utils::ToWString(asMaterial->specularFile);
				fileName = GetTextureName(originName);
				finalPath = _materialPath + fileName;
				auto specular = make_shared<Texture>();
				specular->Create(finalPath);
				material->SetSpecularMap(specular);
				material->GetSpecularMap()->SetName(fileName);
				material->GetSpecularMap()->SetPath(finalPath);
			}
			else
			{
				auto err = make_shared<Texture>();
				err->CreateErrorTexture();
				material->SetSpecularMap(err);
				material->GetSpecularMap()->SetName(fileName);
				material->GetSpecularMap()->SetPath(finalPath);
			}

			material->SetMaterialAttributes(asMaterial->attributes);
		}
		
		bool has_nothing = Material::CheckAttributes(material->_attributes, HAS_NOTHING);
		bool has_diffuse = Material::CheckAttributes(material->_attributes, HAS_DIFFUSE);
		bool has_specular = Material::CheckAttributes(material->_attributes, HAS_SPECULAR);
		bool has_normal = Material::CheckAttributes(material->_attributes, HAS_NORMAL);


		materials.push_back(material);
	}

	model->SetBone(modelBones);
	model->SetMesh(modelMeshes);
	model->SetMaterial(materials);

	return model;
}

