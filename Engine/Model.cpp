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

void Model::LoadFromFiles(const wstring& path)
{
	auto filePath = filesystem::path(path);
	ifstream is(filePath);

	assert(is.is_open(), "failed to open " + Utils::ToString(path));
	assert(!is.fail(), "istream failed");



}
