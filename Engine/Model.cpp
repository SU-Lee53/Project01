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

	shared_ptr<ModelBone> bone = make_shared<ModelBone>();
	shared_ptr<Material> _material = make_shared<Material>();

	LoadNames(is);

	LoadVertices(is, mesh);
	LoadIndices(is, mesh);
	mesh->MakeBuffers();

	LoadBones(is, mesh);
	LoadMaterials(is);

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


}

void Model::LoadMaterials(ifstream& is)
{
}

#pragma endregion Loader