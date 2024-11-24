#pragma once
#include "Collider.h"
#include "Shader.h"

#pragma region DEBUG_MESH
struct ColliderDebugMesh
{
public:
	ColliderDebugMesh()
	{
		_geometry = make_shared<Geometry<DebugType>>();
		_vertexBuffer = make_shared<VertexBuffer>();
		_indexBuffer = make_shared<IndexBuffer>();
		_shader = make_shared<Shader>();
	}

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
public:
	void SetColor(const Color& color) { _color = color; }
	Color GetColor() { return _color; }

	shared_ptr<Geometry<DebugType>> GetGeometry() { return _geometry; }
	shared_ptr<VertexBuffer> GetVertexBuffer() { return _vertexBuffer; }
	shared_ptr<IndexBuffer> GetIndexBuffer() { return _indexBuffer; }
	shared_ptr<Shader> GetShader() { return _shader; }

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

	COLLIDER_TYPE GetColliderType() { return _colliderType; }

	shared_ptr<ColliderDebugMesh> GetDebugMesh() { return _debugMesh; }

protected:
	function<void(Collider c)> _handler;
	Matrix _transform;

protected:
	const COLLIDER_TYPE _colliderType;
	shared_ptr<ColliderDebugMesh> _debugMesh = nullptr;
};

template<typename C>
inline BaseCollider<C>::BaseCollider(COLLIDER_TYPE ty) : _colliderType(ty)
{
}

template<typename C>
inline BaseCollider<C>::~BaseCollider()
{
}
