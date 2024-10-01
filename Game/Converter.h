#pragma once
#include "AsType.h"

// TODO1 : STOP MAKING CONVERTER
// TODO2 : TEXTURE FIRST!!!!

class Converter
{
public:
	Converter();
	~Converter();

public:
	void LoadAssetFile();

public:
	void ReadModel(const aiNode& node, int32 index, int32 parent);

private:
	shared_ptr<Assimp::Importer> _importer;
	const aiScene* _scene;

private:
	vector<shared_ptr<asBone>> _bones;
};
