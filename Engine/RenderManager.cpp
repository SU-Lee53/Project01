#include "EnginePch.h"
#include "RenderManager.h"
#include "GameObject.h"
#include "Pipeline.h"
#include "Shader.h"
#include "MeshRenderer.h"
#include "Mesh.h"

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::Init()
{
	_pipeline = make_shared<Pipeline>();

	_cameraBuffer = make_shared<ConstantBuffer<CameraData>>();
	_transformBuffer = make_shared<ConstantBuffer<TransformData>>();

	_rasterizerState = make_shared<RasterizerState>();
	_blendState = make_shared<BlendState>();
	_samplerState = make_shared<SamplerState>();

	_shader = make_shared<Shader>();

	_cameraBuffer->Create();
	_transformBuffer->Create();

	_rasterizerState->Create();
	_blendState->Create();
	_samplerState->Create();

	_shader->Create();

}

void RenderManager::Update()
{
	_renderObj.clear();
}

void RenderManager::Render()
{
	PushCameraData();

	for (const auto obj : _renderObj)
	{
		auto meshRenderer = obj->GetComponent<MeshRenderer>();
		if (meshRenderer == nullptr)
			continue;

		auto transform = obj->GetComponent<Transform>();
		if (transform == nullptr)
			continue;

		_transformData.matWorld = transform->GetWorld();
		PushTransformData();
		
		_pipeline->SetTexture<PixelShader>(0, meshRenderer->GetTexture());

		PipelineDesc desc;
		{
			desc.inputLayout = _shader->GetInputLayout();
			desc.vertexShader = _shader->GetVertexShader();
			desc.pixelShader = _shader->GetPixelShader();
			desc.rasterizerState = _rasterizerState;
			desc.blendState = _blendState;
		}
		_pipeline->Update(desc);

		_pipeline->SetVertexBuffer(meshRenderer->GetMesh()->GetVertexBuffer());
		_pipeline->SetIndexBuffer(meshRenderer->GetMesh()->GetIndexBuffer());

		_pipeline->SetConstantBuffer<CameraData, VertexShader>(_cameraBuffer);
		_pipeline->SetConstantBuffer<TransformData, VertexShader>(_transformBuffer);

		_pipeline->SetSamplerState<PixelShader>(0, _samplerState);

		_pipeline->DrawIndexed(meshRenderer->GetMesh()->GetIndexBuffer()->GetCount(), 0, 0);
	}


}

void RenderManager::PushCameraData()
{
	_cameraBuffer->PushData(_cameraData);
}

void RenderManager::PushTransformData()
{
	_transformBuffer->PushData(_transformData);
}
