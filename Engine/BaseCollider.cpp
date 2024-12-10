#include "EnginePch.h"
#include "BaseCollider.h"
#include "Shader.h"

BaseCollider::BaseCollider(COLLIDER_TYPE colliderType)
	: _colliderType(colliderType)
{
}

BaseCollider::~BaseCollider()
{
}


/////////////////////////
/////   DebugMesh   /////
/////////////////////////

void DebugMesh::Create(function<void(shared_ptr<Geometry<DebugType>>)> _createFunc)
{
	geometry = make_shared<Geometry<DebugType>>();
	vertexBuffer = make_shared<VertexBuffer>();
	indexBuffer = make_shared<IndexBuffer>();
	shader = make_shared<Shader>();
	colorData = make_shared<ConstantBuffer<Vec4>>();

	_createFunc(geometry);
	vertexBuffer->Create(geometry->GetVertices());
	indexBuffer->Create(geometry->GetIndices());

	shader->SetVertexShader(SHADER->GetVertexShader("ColliderDebug.hlsl"), DebugType::descs);
	shader->SetPixelShader(SHADER->GetPixelShader("ColliderDebug.hlsl"));

	colorData->Create();
	colorData->PushData(color);




}