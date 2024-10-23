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
	void LoadAssetFile(const wstring& modelPath, const wstring& texturePath);

private:
	void ReadModel(const aiNode& node, int32 index, int32 parent);
	void ReadMesh(const aiNode& node, int32 bone);
	void ReadMaterial();

public:
	void Reset();

public:
	void ExportAssetFile(wstring name);

private:
	void ExportModel(wstring name);
	void ExportMaterial(wstring name);

public:
	wstring GetCurrentModelPath() { return _modelPath; }
	wstring GetCurrentMaterialPath() { return _materialPath; }

public:
	// Test
	void ShowMaterials();

public:
	// Just for test : Make model
	shared_ptr<Model> MakeModel();

private:
	shared_ptr<Assimp::Importer> _importer;
	const aiScene* _scene;

private:
	// Import path
	wstring _modelPath = L"";
	wstring _materialPath = L"";

	// Export path
	wstring _modelExportPath = L"../Resources/Models/";
	wstring _materialExportPath = L"../Resources/Materials/";

private:
	vector<shared_ptr<asBone>> _bones;
	vector<shared_ptr<asMesh>> _meshes;
	vector<shared_ptr<asMaterial>> _materials;
};
