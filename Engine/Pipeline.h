#pragma once

class InputLayout;
class Shader;
// TODO : Complete Classes
class RasterizerState;
class SamplerState;
class BlendState;

struct PipelineDesc
{
	shared_ptr<InputLayout> inputLayout;
	shared_ptr<Shader> vertexShader;
	shared_ptr<RasterizerState> rasterizerState;
	shared_ptr<SamplerState> rasterizerState;
	shared_ptr<BlendState> blendState;
	D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

class Pipeline
{
public:
	Pipeline();
	~Pipeline();

public:
	void Update(PipelineDesc desc);


};

