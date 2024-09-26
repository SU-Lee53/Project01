#pragma once
#include "Manager.h"

class GameObject;
class RasterizerState;
class SamplerState;
class BlendState;
class Pipeline;

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
public:
	RenderManager();
	virtual ~RenderManager();

public:
	virtual void Init() override;
	virtual void Update() override;
	void Render();

public:

private:
	shared_ptr<Pipeline> _pipeline;
	vector<shared_ptr<GameObject>> _renderObj;

private:
	shared_ptr<ConstantBuffer<CameraData>> _camera;
	shared_ptr<ConstantBuffer<TransformData>> _transform;

private:
	shared_ptr<Shader> _shader;

public:
	constexpr static  MANAGER_TYPE ty = MANAGER_TYPE::Render;
};

