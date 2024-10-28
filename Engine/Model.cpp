#include "EnginePch.h"
#include "Model.h"
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


/////////////// Load Model From File ///////////////
#pragma region Loader

void Model::LoadFromFiles(const wstring& fileName)
{
	wstring path = L"../Resources/Models/" + fileName;

	auto filePath = filesystem::path(path);
	assert(filesystem::exists(path));

	ifstream is(filePath);
	assert(is.is_open(), "failed to open " + Utils::ToString(path));
	assert(!is.fail(), "istream failed");

	LoadNames(is);
	LoadVertices(is);
	LoadIndices(is);
	LoadBones(is);
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

void Model::LoadVertices(ifstream& is)
{
	assert(is.is_open(), "failed to open " + Utils::ToString(path));
	assert(!is.fail(), "istream failed");

	string read;

	while (true)
	{
		getline(is, read);
		if (read.contains("vertices begin")) break;
	}

	while (true)
	{
		getline(is, read);
		if (read.contains("vertices end")) break;

		// position
		size_t pos = 0;
		size_t prev = 0;

		shared_ptr<ModelMesh> m = make_shared<ModelMesh>();
		VertexType vtx;
		for (int i = 0; i < 3; i++)
		{
			pos = read.find(' ', prev);
			auto sub = read.substr(prev, pos - prev);
			{
				// substr -> pos
				switch (i)
				{
				case 0 :
					vtx.position.x = stof(sub);
					break;
				case 1:
					vtx.position.y = stof(sub);
					break;
				case 2:
					vtx.position.z = stof(sub);
					break;
				default:
					assert(false);
				}

			}
			prev = pos + 1;
		}

		// uv
		getline(is, read);
		for (int i = 0; i < 2; i++)
		{
			pos = read.find(' ', prev);
			auto sub = read.substr(prev, pos - prev);
			{
				// substr -> pos
				switch (i)
				{
				case 0:
					vtx.uv.x = stof(sub);
					break;
				case 1:
					vtx.uv.y = stof(sub);
					break;
				default:
					assert(false);
				}
			}
			prev = pos + 1;
		}

		// normal
		getline(is, read);
		for (int i = 0; i < 3; i++)
		{
			pos = read.find(' ', prev);
			auto sub = read.substr(prev, pos - prev);
			{
				// substr -> pos
				switch (i)
				{
				case 0:
					vtx.normal.x = stof(sub);
					break;
				case 1:
					vtx.normal.y = stof(sub);
					break;
				case 2:
					vtx.normal.z = stof(sub);
					break;
				default:
					assert(false);
				}
			}
			prev = pos + 1;
		}

		// tangent
		getline(is, read);
		for (int i = 0; i < 3; i++)
		{
			pos = read.find(' ', prev);
			auto sub = read.substr(prev, pos - prev);
			{
				// substr -> pos
				switch (i)
				{
				case 0:
					vtx.tangent.x = stof(sub);
					break;
				case 1:
					vtx.tangent.y = stof(sub);
					break;
				case 2:
					vtx.tangent.z = stof(sub);
					break;
				default:
					assert(false);
				}
			}
			prev = pos + 1;
		}
		

		// Add
		m->geometry->AddVertex(vtx);
	}

}

void Model::LoadIndices(ifstream& is)
{
}

void Model::LoadBones(ifstream& is)
{
}

void Model::LoadMaterials(ifstream& is)
{
}

#pragma endregion Loader