#include "EnginePch.h"
#include "RenderManager.h"
#include "GameObject.h"
#include "Pipeline.h"
#include "Shader.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Model.h"
#include "BaseCollider.h"
#include "Scene.h"
#include "Camera.h"

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
	_materialBuffer = make_shared<ConstantBuffer<MaterialData>>();
	_globalBuffer = make_shared<ConstantBuffer<GlobalLightData>>();

	_rasterizerState = make_shared<RasterizerState>();
	_blendState = make_shared<BlendState>();
	_samplerState = make_shared<SamplerState>();

	_shader = make_shared<Shader>();

	_cameraBuffer->Create();
	_transformBuffer->Create();
	_materialBuffer->Create();
	_globalBuffer->Create();

	_rasterizerState->Create();
	_blendState->Create();
	_samplerState->Create();

	_shader->CreateDefault();


	_wireframeRasterizer = make_shared<RasterizerState>();
	{
		D3D11_RASTERIZER_DESC _debugRasterizerDesc;
		memset(&_debugRasterizerDesc, 0, sizeof(_debugRasterizerDesc));
		{
			_debugRasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
			_debugRasterizerDesc.CullMode = D3D11_CULL_BACK;
			_debugRasterizerDesc.FrontCounterClockwise = false;
		}

		ComPtr<ID3D11RasterizerState> _debugRasterizer;
		HR_ASSERT(DEVICE->CreateRasterizerState(&_debugRasterizerDesc, _debugRasterizer.GetAddressOf()));
		_wireframeRasterizer->SetState(_debugRasterizer);
	}

}

void RenderManager::Update()
{
	_renderObj.clear();
	_debugMeshes.clear();
}

void RenderManager::Render()
{
	CUR_SCENE->GetMainCamera()->GetComponent<Camera>()->PushCamera();
	PushCameraData();
	PushGlobalLightData();
	for (const auto obj : _renderObj)
	{
		auto meshRenderer = obj->GetComponent<MeshRenderer>();
		if (meshRenderer == nullptr)
			continue;

		auto transform = obj->GetComponent<Transform>();
		if (transform == nullptr)
			continue;

		if (obj->GetComponent<MeshRenderer>()->GetModel() == nullptr)
		{
			RenderLagacy(obj);
		}
		else
		{
			RenderModel(obj);
		}

	}

#ifdef _DEBUG
	for (const auto mesh : _debugMeshes)
	{
		RenderColliderDebugMesh(mesh);
	}

#endif
}

void RenderManager::RenderLagacy(shared_ptr<GameObject> obj)
{
	auto meshRenderer = obj->GetComponent<MeshRenderer>();

	auto transform = obj->GetComponent<Transform>();

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

void RenderManager::RenderModel(shared_ptr<GameObject> obj)
{
	auto meshRenderer = obj->GetComponent<MeshRenderer>();
	auto transform = obj->GetTransform();
	_transformData.matWorld = transform->GetWorld();

	auto model = meshRenderer->GetModel();

	auto bones = model->GetBones();
	auto meshes = model->GetMeshes();
	auto materials = model->GetMaterials();

	for (const auto mesh : meshes)
	{
		int32 boneIndex = mesh->boneIndex;
		_transformData.matLocal = transform->GetLocal();
		//_transformData.matLocal = bones[boneIndex]->transform;
		PushTransformData();

		//auto material = RESOURCE->Get<Material>(Utils::ToString(mesh->materialName));
		auto material = materials[mesh->materialIndex];
		_materialData = material->GetMaterialData();
		PushMaterialData();

		_pipeline->SetTexture<PixelShader>(Material::_diffuseSlot, material->GetDiffuseMap());
		_pipeline->SetTexture<PixelShader>(Material::_normalSlot, material->GetNormalMap());
		_pipeline->SetTexture<PixelShader>(Material::_specularSlot, material->GetSpecularMap());

		PipelineDesc desc;
		{
			desc.inputLayout = _shader->GetInputLayout();
			//desc.vertexShader = _shader->GetVertexShader();
			//desc.pixelShader = _shader->GetPixelShader();
			desc.vertexShader = material->GetVertexShader();
			desc.pixelShader = material->GetPixelShader();
			desc.rasterizerState = _rasterizerState;
			desc.blendState = _blendState;
		}
		_pipeline->Update(desc);

		_pipeline->SetVertexBuffer(mesh->vertexBuffer);
		_pipeline->SetIndexBuffer(mesh->indexBuffer);

		_pipeline->SetConstantBuffer<CameraData, VertexShader>(_cameraBuffer);
		_pipeline->SetConstantBuffer<TransformData, VertexShader>(_transformBuffer);
		
		_pipeline->SetConstantBuffer<MaterialData, PixelShader>(_materialBuffer);
		_pipeline->SetConstantBuffer<GlobalLightData, PixelShader>(_globalBuffer);

		_pipeline->SetSamplerState<PixelShader>(0, _samplerState);

		_pipeline->DrawIndexed(mesh->indexBuffer->GetCount(), 0, 0);
	}

}

void RenderManager::RenderColliderDebugMesh(shared_ptr<DebugMesh> mesh)
{
	// Wireframe Rasterizer
	_transformData.matWorld = mesh->transfom;
	PushTransformData();

	PipelineDesc desc;
	{
		desc.inputLayout = mesh->shader->GetInputLayout();
		desc.vertexShader = mesh->shader->GetVertexShader();
		desc.pixelShader = mesh->shader->GetPixelShader();
		desc.rasterizerState = _wireframeRasterizer;
		desc.blendState = _blendState;
	}
	_pipeline->Update(desc);
	

	_pipeline->SetVertexBuffer(mesh->vertexBuffer);
	_pipeline->SetIndexBuffer(mesh->indexBuffer);

	_pipeline->SetConstantBuffer<CameraData, VertexShader>(_cameraBuffer);
	_pipeline->SetConstantBuffer<TransformData, VertexShader>(_transformBuffer);

	_pipeline->SetSamplerState<PixelShader>(0, _samplerState);

	_pipeline->DrawIndexed(mesh->indexBuffer->GetCount(), 0, 0);
}

void RenderManager::PushCameraData()
{
	_cameraBuffer->PushData(_cameraData);
}

void RenderManager::PushTransformData()
{
	_transformBuffer->PushData(_transformData);
}

void RenderManager::PushMaterialData()
{
	_materialBuffer->PushData(_materialData);
}

void RenderManager::PushGlobalLightData()
{
	_globalBuffer->PushData(_globalLightData);
}
