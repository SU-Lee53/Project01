#pragma once
#include "Manager.h"
#include "Constant_Types.h"
#include "ConstantBuffer.h"

class GameObject;
class RasterizerState;
class SamplerState;
class BlendState;
class Pipeline;
class Shader;

struct DebugMesh;

class RenderManager : public Manager_Base
{
	// TODO : Add Texture for future
public:
	RenderManager();
	virtual ~RenderManager();

public:
	virtual void Init() override;
	virtual void Update() override;
	void Render();

private:
	void RenderLagacy(shared_ptr<GameObject> obj);
	void RenderModel(shared_ptr<GameObject> obj);
	void RenderColliderDebugMesh(shared_ptr<DebugMesh> mesh);

public:
	void PushToRenderObject(shared_ptr<GameObject> obj) { _renderObj.push_back(obj); }
	void PushToDebugMesh(shared_ptr<DebugMesh> obj) { _debugMeshes.push_back(obj); }

private:
	void PushCameraData();
	void PushTransformData();
	void PushMaterialData();
	void PushGlobalLightData();

public:
	void SetRasterizerState(shared_ptr<RasterizerState> rs) { _rasterizerState = rs; }
	void SetBlendState(shared_ptr<BlendState> bs) { _blendState = bs; }
	void SetSamplerState(shared_ptr<SamplerState> ss) { _samplerState = ss; }

public:
	void SetCameraData(const CameraData& cam) { _cameraData = cam; }
	void SetMaterialData(const MaterialData& material) { _materialData = material; }
	void SetGlobalLightData(const GlobalLightData& light) { _globalLightData = light; }

private:
	shared_ptr<Pipeline> _pipeline;
	vector<shared_ptr<GameObject>> _renderObj;

	// for collider debug
	vector<shared_ptr<DebugMesh>> _debugMeshes;

private:
	CameraData _cameraData;
	shared_ptr<ConstantBuffer<CameraData>> _cameraBuffer;

	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _transformBuffer;

	MaterialData _materialData;
	shared_ptr<ConstantBuffer<MaterialData>> _materialBuffer;
	
	GlobalLightData _globalLightData;
	shared_ptr<ConstantBuffer<GlobalLightData>> _globalBuffer;

private:
	shared_ptr<Shader> _shader;
	shared_ptr<RasterizerState> _rasterizerState;
	shared_ptr<BlendState> _blendState;
	shared_ptr<SamplerState> _samplerState;

	shared_ptr<RasterizerState> _wireframeRasterizer;

public:
	constexpr static  MANAGER_TYPE ty = MANAGER_TYPE::Render;
};

