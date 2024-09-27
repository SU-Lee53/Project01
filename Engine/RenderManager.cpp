#include "EnginePch.h"
#include "RenderManager.h"
#include "GameObject.h"
#include "Pipeline.h"
#include "Shader.h"

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::Init()
{
	_pipeline = make_shared<Pipeline>();

	_camera = make_shared<ConstantBuffer<CameraData>>();
	_transform = make_shared<ConstantBuffer<TransformData>>();

	_rasterizerState = make_shared<RasterizerState>();
	_blendState = make_shared<BlendState>();
	_samplerState = make_shared<SamplerState>();

	_shader = make_shared<Shader>();

	_camera->Create();
	_transform->Create();

	_rasterizerState->Create();
	_blendState->Create();
	_samplerState->Create();

	_shader->Create();

}

void RenderManager::Update()
{
	PipelineDesc desc;
	memset(&desc, 0, sizeof(desc));
	{
		desc.inputLayout = _shader->GetInputLayout();
		desc.vertexShader = _shader->GetVertexShader();
		desc.pixelShader = _shader->GetPixelShader();
		desc.rasterizerState = _rasterizerState;
		desc.blendState = _blendState;
	}

	_pipeline->Update(desc);


	_renderObj.clear();
}

void RenderManager::Render()
{

}
