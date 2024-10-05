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



private:
	shared_ptr<ModelBone> _root;
	vector<shared_ptr<ModelBone>> _bones;
	vector<shared_ptr<ModelMesh>> _meshes;
	vector<shared_ptr<Material>> _material;


};

