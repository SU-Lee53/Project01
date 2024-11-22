#pragma once
#include "Collider.h"
#include "Shader.h"

#pragma region DEBUG_MESH
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

public:
	void SetColor(const Color& color) { _color = color; }
	Color GetColor() { return _color; }

	shared_ptr<Geometry<DebugType>> GetGeometry() { return _geometry; }
	shared_ptr<VertexBuffer> GetVertexBuffer() { return _vertexBuffer; }
	shared_ptr<IndexBuffer> GetIndexBuffer() { return _indexBuffer; }

private:
	shared_ptr<Geometry<DebugType>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<Shader> _shader;
	Color _color = Color{ 1.f,1.f,1.f,1.f };

};
#pragma endregion DEBUG_MESH

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

	virtual void CreateDebugMesh() { assert(false); }

	COLLIDER_TYPE GetColliderType() { return _colliderType; }

protected:
	const COLLIDER_TYPE _colliderType;
	shared_ptr<ColliderDebugMesh> _debugMesh;
};

template<typename C>
inline BaseCollider<C>::BaseCollider(COLLIDER_TYPE ty) : _colliderType(ty)
{
}

template<typename C>
inline BaseCollider<C>::~BaseCollider()
{
}
