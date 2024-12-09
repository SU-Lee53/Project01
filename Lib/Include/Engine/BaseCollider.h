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
	DebugMesh() = default;

	void Create(function<void(shared_ptr<Geometry<DebugType>>)> _createFunc)
	{
		geometry = make_shared<Geometry<DebugType>>();
		vertexBuffer = make_shared<VertexBuffer>();
		indexBuffer = make_shared<IndexBuffer>();

		_createFunc(geometry);
		vertexBuffer->Create(geometry->GetVertices());
		indexBuffer->Create(geometry->GetIndices());
	}

	shared_ptr<Geometry<DebugType>> geometry;
	shared_ptr<VertexBuffer> vertexBuffer;
	shared_ptr<IndexBuffer> indexBuffer;
	Color color = Color(1.f, 0.f, 0.f, 0.f);

	Matrix transfom = Matrix::Identity;
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
	shared_ptr<DebugMesh> GetDebugMesh() { return _debugMesh; }

protected:
	Matrix _transform = Matrix::Identity;

protected:
	shared_ptr<DebugMesh> _debugMesh = nullptr;

public:
	COLLIDER_TYPE _colliderType;
	//constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::Collider;
};

