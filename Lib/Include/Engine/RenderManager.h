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

public:
	void PushToRenderObject(shared_ptr<GameObject> obj) { _renderObj.push_back(obj); }

private:
	void PushCameraData();
	void PushTransformData();

public:
	void SetRasterizerState(shared_ptr<RasterizerState> rs) { _rasterizerState = rs; }
	void SetRasterizerState(shared_ptr<BlendState> bs) { _blendState = bs; }
	void SetRasterizerState(shared_ptr<SamplerState> ss) { _samplerState = ss; }

public:
	void SetCameraData(CameraData cam) { _cameraData = cam; }

private:
	shared_ptr<Pipeline> _pipeline;
	vector<shared_ptr<GameObject>> _renderObj;

private:
	CameraData _cameraData;
	shared_ptr<ConstantBuffer<CameraData>> _cameraBuffer;

	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _transformBuffer;

	MaterialData _materialData;
	shared_ptr<ConstantBuffer<MaterialData>> _materialBuffer;

private:
	shared_ptr<Shader> _shader;
	shared_ptr<RasterizerState> _rasterizerState;
	shared_ptr<BlendState> _blendState;
	shared_ptr<SamplerState> _samplerState;

public:
	constexpr static  MANAGER_TYPE ty = MANAGER_TYPE::Render;
};

