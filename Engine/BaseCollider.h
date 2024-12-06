#pragma once
#include "Component.h"

enum class COLLIDER_TYPE
{
	Sphere,
	AABB,
	Plane
};

struct DebugMesh
{
	shared_ptr<Geometry<DebugType>> geometry;
	shared_ptr<VertexBuffer> vertexBuffer;
	shared_ptr<IndexBuffer> indexBuffer;
	Color color = Color(1.f, 0.f, 0.f, 0.f);
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

protected:
	Matrix _transform = Matrix::Identity;

protected:
	shared_ptr<Geometry<DebugType>> _debugMesh;

public:
	COLLIDER_TYPE _colliderType;
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::Collider;
};

