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

	void SetBone(vector<shared_ptr<ModelBone>> bone) { _bones = bone; }
	void AddBone(shared_ptr<ModelBone> bone) { _bones.push_back(bone); }

	void SetMesh(vector<shared_ptr<ModelMesh>> mesh) { _meshes = mesh;}
	void AddMesh(shared_ptr<ModelMesh> mesh) { _meshes.push_back(mesh); }

	void SetMaterial(vector<shared_ptr<Material>> material) { _material = material; }
	void AddMaterial(shared_ptr<Material> material) { _material.push_back(material); }

	auto GetBones() const { return _bones; }
	auto GetMeshes() const { return _meshes; }
	auto GetMaterials() const { return _material; }

private:
	shared_ptr<ModelBone> _root;
	vector<shared_ptr<ModelBone>> _bones;
	vector<shared_ptr<ModelMesh>> _meshes;
	vector<shared_ptr<Material>> _material;


};

