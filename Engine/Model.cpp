#include "EnginePch.h"
#include "Model.h"
#include "Material.h"
#include <filesystem>

Model::Model()
{
}

Model::~Model()
{
}

void Model::SetBone(vector<shared_ptr<ModelBone>> bone)
{
	_bones = bone;
	_root = bone[0];
}


/////////////// Load Model From .mesh File ///////////////
#pragma region Loader

void Model::LoadFromFiles(const wstring& fileName)
{
	wstring path = L"../Resources/Models/" + fileName;

	auto filePath = filesystem::path(path);
	assert(filesystem::exists(path));

	ifstream is(filePath);
	assert(is.is_open(), "failed to open " + Utils::ToString(path));
	assert(!is.fail(), "istream failed");

	shared_ptr<ModelMesh> mesh = make_shared<ModelMesh>();
	mesh->geometry = make_shared<Geometry<VertexType>>();

	shared_ptr<Material> material = make_shared<Material>();

	LoadNames(is);

	LoadVertices(is, mesh);
	LoadIndices(is, mesh);
	mesh->MakeBuffers();

	LoadBones(is, mesh);
	LoadMaterials(is, material);

}

		//////////////////////////////////
		// 3 steps						//
		// 1. check ### begin			//
		// 2. read until ### end shows	//
		// 3. modify					//
		//////////////////////////////////

void Model::LoadNames(ifstream& is)
{
	assert(is.is_open(), "failed to open " + Utils::ToString(path));
	assert(!is.fail(), "istream failed");

	string read;

	while (true)
	{
		getline(is, read);
		if (read.contains("names begin")) break;
	}

	while (true)
	{
		getline(is, read);
		if (read.contains("names end")) break;
		
		// we don't have names yet so skip this part
	}

}

void Model::LoadVertices(ifstream& is, OUT shared_ptr<ModelMesh> mesh)
{
	assert(is.is_open(), "failed to open " + Utils::ToString(path));
	assert(!is.fail(), "istream failed");

	string read;

	while (true)
	{
		getline(is, read);
		if (read.contains("vertices begin")) break;
	}

	vector<VertexType> vertices;

	while (true)
	{
		getline(is, read);
		if (read.contains("vertices end")) break;

		VertexType vtx;
		float vec[3];

		// position
		size_t pos = 0;
		size_t prev = 0;

		for (int i = 0; i < 3; i++)
		{
			pos = read.find(' ', prev);
			auto sub = read.substr(prev, pos - prev);
			{
				vec[i] = stof(sub);
			}
			prev = pos + 1;
		}
		vtx.position = Vec3(vec);

		// uv
		getline(is, read);
		for (int i = 0; i < 2; i++)
		{
			pos = read.find(' ', prev);
			auto sub = read.substr(prev, pos - prev);
			{
				vec[i] = stof(sub);
			}
			prev = pos + 1;
		}
		vtx.uv = Vec2(vec);

		// normal
		getline(is, read);
		for (int i = 0; i < 3; i++)
		{
			pos = read.find(' ', prev);
			auto sub = read.substr(prev, pos - prev);
			{
				// substr -> pos
				vec[i] = stof(sub);
			}
			prev = pos + 1;
		}
		vtx.normal = Vec3(vec);

		// tangent
		getline(is, read);
		for (int i = 0; i < 3; i++)
		{
			pos = read.find(' ', prev);
			auto sub = read.substr(prev, pos - prev);
			{
				// substr -> pos
				vec[i] = stof(sub);
			}
			prev = pos + 1;
		}
		vtx.tangent = Vec3(vec);
		
		// Add
		vertices.push_back(vtx);
	}

	mesh->geometry->SetVertices(vertices);

}

void Model::LoadIndices(ifstream& is, OUT shared_ptr<ModelMesh> mesh)
{
	assert(is.is_open(), "failed to open " + Utils::ToString(path));
	assert(!is.fail(), "istream failed");

	string read;

	while (true)
	{
		getline(is, read);
		if (read.contains("indices begin")) break;
	}

	vector<uint32> indices;

	while (true)
	{
		getline(is, read);
		if (read.contains("indices end")) break;

		uint32 idx = stoi(read);
		indices.push_back(idx);
	}

	mesh->geometry->SetIndices(indices);

}

void Model::LoadBones(ifstream& is, OUT shared_ptr<ModelMesh> mesh)
{
	assert(is.is_open(), "failed to open " + Utils::ToString(path));
	assert(!is.fail(), "istream failed");

	string read;

	while (true)
	{
		getline(is, read);
		if (read.contains("bones begin")) break;
	}

	// boneIndex
	getline(is, read);
	mesh->boneIndex = stoi(read);

	while(true)
	{
		getline(is, read);
		if (read.contains("bones end")) break;
		
		shared_ptr<ModelBone> bone = make_shared<ModelBone>();

		// name
		bone->name = Utils::ToWString(read);

		// index
		getline(is, read);
		bone->index = stoi(read);

		// parent
		getline(is, read);
		bone->parentIndex = stoi(read);

		// transform
		size_t pos = 0;
		size_t prev = 0;
		float matrix[4][4]; 

		for (uint32 i = 0; i < 4; i++)
		{
			getline(is, read);
			for (uint32 j = 0; j < 4; j++)
			{
				pos = read.find(' ', prev);
				auto sub = read.substr(prev, pos - prev);
				{
					// substr -> pos'
					matrix[i][j] = stof(sub);
				}
				prev = pos + 1;
			}
		}
		bone->transform = Matrix((float*)matrix);

		_bones.push_back(bone);
	}

	_root = _bones.front();

}

void Model::LoadMaterials(ifstream& is, OUT shared_ptr<Material> material)
{
	assert(is.is_open(), "failed to open " + Utils::ToString(path));
	assert(!is.fail(), "istream failed");

	string read;

	while (true)
	{
		getline(is, read);
		if (read.contains("materials begin")) break;
	}

	while (true)
	{
		getline(is, read);
		if (read.contains("materials end")) break;

		// material name
		wstring name = Utils::ToWString(read);
		material->SetName(name);

		float color[4];
		MaterialData data;

		size_t pos = 0;
		size_t prev = 0;

		// Material Data(colors)
		{
			// diffuse
			getline(is, read);
			for (int i = 0; i < 4; i++)
			{
				pos = read.find(' ', prev);
				auto sub = read.substr(prev, pos - prev);
				{
					color[i] = stof(sub);
				}
				prev = pos + 1;
			}
			data.diffuse = Color(color);

			// specular
			getline(is, read);
			for (int i = 0; i < 4; i++)
			{
				pos = read.find(' ', prev);
				auto sub = read.substr(prev, pos - prev);
				{
					color[i] = stof(sub);
				}
				prev = pos + 1;
			}
			data.specular = Color(color);

			// ambient
			getline(is, read);
			for (int i = 0; i < 4; i++)
			{
				pos = read.find(' ', prev);
				auto sub = read.substr(prev, pos - prev);
				{
					color[i] = stof(sub);
				}
				prev = pos + 1;
			}
			data.ambient = Color(color);

			// emissive
			getline(is, read);
			for (int i = 0; i < 4; i++)
			{
				pos = read.find(' ', prev);
				auto sub = read.substr(prev, pos - prev);
				{
					color[i] = stof(sub);
				}
				prev = pos + 1;
			}
			data.ambient = Color(color);
		}

		material->SetMaterialData(data);

		// textures
		{
			wstring path = L"../Resources/Materials/Texture/" + material->GetName() + L'/';
			uint8 flag = 0;

			for (uint32 i = 0; i < 3; i++)
			{
				shared_ptr<Texture> tex = make_shared<Texture>();

				getline(is, read);
				if (read != "None")
				{
					string fileName = filesystem::path(read).filename().string();
					wstring filePath = path + Utils::ToWString(fileName);
					tex->Create(filePath);
				}
				else
				{
					tex->CreateErrorTexture();
				}

				switch (i)
				{
				case 0:
					material->SetDiffuseMap(tex);
					if (tex->IsErrorTexture() == false)
					{
						flag |= HAS_DIFFUSE;
					}
					break;

				case 1:
					material->SetSpecularMap(tex);
					if (tex->IsErrorTexture() == false)
					{
						flag |= HAS_SPECULAR;
					}
					break;

				case 2:
					material->SetNormalMap(tex);
					if (tex->IsErrorTexture() == false)
					{
						flag |= HAS_NORMAL;
					}
					break;

				default:
					assert(false);
				}

			}

			material->SetMaterialAttributes((MaterialFlag)flag);
		}

		// TODO : Set Shader by Attribute(flag)


	}


}

#pragma endregion Loader