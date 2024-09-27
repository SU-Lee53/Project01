#pragma once
#include "Manager.h"

class GameObject;
class RasterizerState;
class SamplerState;
class BlendState;
class Pipeline;
class Shader;

struct CameraData
{
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;
};

struct TransformData
{
	Matrix matWorld = Matrix::Identity;
};

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

public:
	void SetRasterizerState(shared_ptr<RasterizerState> rs) { _rasterizerState = rs; }
	void SetRasterizerState(shared_ptr<BlendState> bs) { _blendState = bs; }
	void SetRasterizerState(shared_ptr<SamplerState> ss) { _samplerState = ss; }


private:
	shared_ptr<Pipeline> _pipeline;
	vector<shared_ptr<GameObject>> _renderObj;

private:
	shared_ptr<ConstantBuffer<CameraData>> _camera;
	shared_ptr<ConstantBuffer<TransformData>> _transform;

	shared_ptr<RasterizerState> _rasterizerState;
	shared_ptr<BlendState> _blendState;
	shared_ptr<SamplerState> _samplerState;

private:
	shared_ptr<Shader> _shader;


public:
	constexpr static  MANAGER_TYPE ty = MANAGER_TYPE::Render;
};

