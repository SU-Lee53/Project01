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

	void Create(function<void(shared_ptr<Geometry<DebugType>>)> _createFunc);

	void SetColor(Color c)
	{
		color = c;
		colorData->PushData(color);
	}

	shared_ptr<Geometry<DebugType>> geometry;
	shared_ptr<VertexBuffer> vertexBuffer;
	shared_ptr<IndexBuffer> indexBuffer;
	shared_ptr<Shader> shader;
	Color color = Color(1.f, 0.f, 0.f, 1.f);
	shared_ptr<ConstantBuffer<Vec4>> colorData;

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
	virtual void InitCollider() { assert(false); }
	virtual void UpdateCollider() { assert(false); }

public:
	virtual bool CheckCollision(shared_ptr<BaseCollider> other) { assert(false); return false; }

public:
	COLLIDER_TYPE GetColliderType() { return _colliderType; }

public:
	shared_ptr<DebugMesh> GetDebugMesh() { return _debugMesh; }

protected:
	shared_ptr<DebugMesh> _debugMesh = nullptr;

public:
	COLLIDER_TYPE _colliderType;
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::Collider;
};


template <typename C>
concept IsColliderType = requires (C c)
{
	derived_from<BaseCollider, C>;
};

template <typename C>
concept ColliderType = IsColliderType<C>;
