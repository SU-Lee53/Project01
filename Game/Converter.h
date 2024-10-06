#pragma once
#include "AsType.h"

class Model;

class Converter
{
public:
	Converter();
	~Converter();

public:
	void LoadAssetFile();

private:
	void ReadModel(const aiNode& node, int32 index, int32 parent);
	void ReadMesh(const aiNode& node, int32 bone);
	void ReadMaterial();

public:
	void ExportAssetFile();

private:
	void ExportModel();
	void ExportMesh();
	void ExportMaterial();

public:
	// Just for test : Make model
	shared_ptr<Model> MakeModel();

private:
	shared_ptr<Assimp::Importer> _importer;
	const aiScene* _scene;

private:
	wstring _modelPath = L"../Resources/Models/";
	wstring _texturePath = L"../Resources/Textures/";

private:
	vector<shared_ptr<asBone>> _bones;
	vector<shared_ptr<asMesh>> _meshes;
	vector<shared_ptr<asMaterial>> _materials;
};
