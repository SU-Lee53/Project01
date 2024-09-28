#pragma once
#include "Manager.h"
#include "Constant_Types.h"

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
	void PushCameraData();
	void PushTransformData();

public:
	void SetRasterizerState(shared_ptr<RasterizerState> rs) { _rasterizerState = rs; }
	void SetRasterizerState(shared_ptr<BlendState> bs) { _blendState = bs; }
	void SetRasterizerState(shared_ptr<SamplerState> ss) { _samplerState = ss; }

public:
	void SetCameraData(shared_ptr<ConstantBuffer<CameraData>> cam) { _camera = cam; }

private:
	shared_ptr<Pipeline> _pipeline;
	vector<shared_ptr<GameObject>> _renderObj;

private:
	shared_ptr<ConstantBuffer<CameraData>> _camera;
	shared_ptr<ConstantBuffer<TransformData>> _transform;

private:
	shared_ptr<Shader> _shader;
	shared_ptr<RasterizerState> _rasterizerState;
	shared_ptr<BlendState> _blendState;
	shared_ptr<SamplerState> _samplerState;

public:
	constexpr static  MANAGER_TYPE ty = MANAGER_TYPE::Render;
};

