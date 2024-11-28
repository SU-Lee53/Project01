#pragma once
#include "Resource_Base.h"

class Mesh;
class Material;
class Texture;

class Model : public Resource_Base
{
public:
	Model();
	virtual ~Model();

	void SetBone(vector<shared_ptr<ModelBone>> bone);
	void AddBone(shared_ptr<ModelBone> bone) { _bones.push_back(bone); }

	void SetMesh(vector<shared_ptr<ModelMesh>> mesh) { _meshes = mesh;}
	void AddMesh(shared_ptr<ModelMesh> mesh) { _meshes.push_back(mesh); }

	void SetMaterial(vector<shared_ptr<Material>> material) { _materials = material; }
	void AddMaterial(shared_ptr<Material> material) { _materials.push_back(material); }

	auto GetRootBone() const { return _root; }
	auto GetBones() const { return _bones; }
	auto GetMeshes() const { return _meshes; }
	auto GetMaterials() const { return _materials; }

public:
	void LoadFromFiles(const wstring& path);

private:
	void LoadNames(ifstream& is);
	void LoadVertices(ifstream& is, OUT shared_ptr<ModelMesh> mesh);
	void LoadIndices(ifstream& is, OUT shared_ptr<ModelMesh> mesh);
	void LoadBones(ifstream& is, OUT shared_ptr<ModelMesh> mesh);
	void LoadMaterials(ifstream& is);

public:
	void ShowModelHierarchy();

private:
	void ShowBoneNode(shared_ptr<ModelBone> node, vector<shared_ptr<ModelBone>> all_nodes);

private:
	shared_ptr<ModelBone> _root;
	vector<shared_ptr<ModelBone>> _bones;
	vector<shared_ptr<ModelMesh>> _meshes;
	vector<shared_ptr<Material>> _materials;


};

