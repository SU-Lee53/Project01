#pragma once
#include "Script.h"

class Model;

class ModelScript : public Script<GameObject>
{
public:
	virtual void Init() override;
	virtual void Update() override;

private:
	bool HasParent(int index);
	bool HasChild(int index);
	bool IsRoot(int index);

private:
	friend class Test;

	weak_ptr<Model> _model;
	Matrix _transform;
	float _dragSpeed = 0.1f;
};

