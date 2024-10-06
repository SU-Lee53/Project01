#include "EnginePch.h"
#include "Model.h"

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