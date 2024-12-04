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
	void Init_impl()
	{
		InitCollider();
	}

	void Update_impl()
	{
		UpdateCollider();
	}

protected:
	virtual void InitCollider() = 0;
	virtual void UpdateCollider() = 0;

public:
	virtual bool CheckCollision(shared_ptr<BaseCollider> other) = 0;

public:
	COLLIDER_TYPE GetColliderType() { return _colliderType; }

public:
	shared_ptr<Geometry<DebugType>> GetDebugMesh() { return _debugMesh; }

private:
	Matrix _transform;

private:
	shared_ptr<Geometry<DebugType>> _debugMesh;

public:
	COLLIDER_TYPE _colliderType;
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::Collider;
};

