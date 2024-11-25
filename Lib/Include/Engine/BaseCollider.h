#pragma once
#include "Component.h"

enum class COLLIDER_TYPE
{
	Sphere,
	AABB,
	Plane
};

class BaseCollider : public Component<BaseCollider>
{
public:
	BaseCollider(COLLIDER_TYPE type);
	virtual ~BaseCollider();

public:
	void Update_impl()
	{
		UpdateCollider();
	}

protected:
	virtual void UpdateCollider() = 0;

public:
	virtual bool CheckCollision(shared_ptr<BaseCollider> other) = 0;

public:
	COLLIDER_TYPE GetColliderType() { return _colliderType; }

protected:
	COLLIDER_TYPE _colliderType;
};

