#pragma once

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

class RenderManager
{
public:
	RenderManager();
	~RenderManager();

public:
	void Init();
	void Update();
	void Render();

public:

private:
	shared_ptr<Pipeline> _pipeline;
	vector<shared_ptr<GameObject>> _renderObj;

private:
	shared_ptr<ConstantBuffer<CameraData>> _camera;
	shared_ptr<ConstantBuffer<TransformData>> _transform;

private:
	shared_ptr<RasterizerState> _rasterizerState;
	shared_ptr<SamplerState> _samplerState;
	shared_ptr<BlendState> _blendState;

};

