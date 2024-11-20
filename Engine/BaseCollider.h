#pragma once
#include "Collider.h"
#include "Shader.h"

struct ColliderDebugMesh
{
public:
	void Create()
	{
		SetShader();
		CreateBuffers();
	}

private:
	void SetShader()
	{
		_shader = make_shared<Shader>();
		_shader->SetVertexShader(SHADER->GetVertexShader("ColliderDebug.hlsl"), DebugType::descs);
		_shader->SetPixelShader(SHADER->GetPixelShader("ColliderDebug.hlsl"));
	}

	void CreateBuffers()
	{
		_vertexBuffer = make_shared<VertexBuffer>();
		_vertexBuffer->Create(_geometry->GetVertices());

		_indexBuffer = make_shared<IndexBuffer>();
		_indexBuffer->Create(_geometry->GetIndices());
	}

private:
	// make primitive mesh for debug
	// move seperately in near future!!!
	template <ColliderType C>
	void MakeDebugMesh()
	{
	}

private:
	shared_ptr<Geometry<VertexType>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	shared_ptr<Shader> _shader;

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
