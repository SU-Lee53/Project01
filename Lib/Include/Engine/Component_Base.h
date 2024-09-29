#pragma once
#include "RenderManager.h"

class Transform;
class GameObject;

class Component_Base
{
public:
	Component_Base() {}
	virtual ~Component_Base() {}

public:
	virtual void Init() {}
	virtual void Update() {}

public:
	shared_ptr<GameObject> GetOwner();
	shared_ptr<Transform> GetTransform();

protected:
	friend class GameObject;
	void SetOwner(shared_ptr<GameObject> gameObject);
	weak_ptr<GameObject> _owner;

};
