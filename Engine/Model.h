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
	vector<shared_ptr<Mesh>> _meshes;
	vector<shared_ptr<Material>> _material;


};

