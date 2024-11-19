#pragma once
#include "Collider.h"

struct ColliderDebugMesh
{
public:
	void CreateBuffers()
	{
		_vertexBuffer = make_shared<VertexBuffer>();
		_vertexBuffer->Create(_geometry->GetVertices());

		_indexBuffer = make_shared<IndexBuffer>();
		_indexBuffer->Create(_geometry->GetIndices());
	}

private:
	shared_ptr<Geometry<VertexType>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

};

template <typename C>
class BaseCollider : public Collider
{
	static_assert(IsColliderType<C>);

public:
	BaseCollider(COLLIDER_TYPE ty);
	virtual ~BaseCollider();

public:
	virtual void InitCollider() override
	{
		(static_cast<C*>(this))->UpdateCollider();
	}

	virtual void UpdateCollider() override
	{
		(static_cast<C*>(this))->UpdateCollider();
	}

protected:
	const COLLIDER_TYPE _colliderType;

};

template<typename C>
inline BaseCollider<C>::BaseCollider(COLLIDER_TYPE ty) : _colliderType(ty)
{
}

template<typename C>
inline BaseCollider<C>::~BaseCollider()
{
}
