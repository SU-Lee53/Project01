#pragma once

#include "InputLayout.h"
#include "Shader.h"
#include "RasterizerState.h"
#include "SamplerState.h"
#include "BlendState.h"

struct PipelineDesc
{
	shared_ptr<InputLayout> inputLayout;
	shared_ptr<Shader<ID3D11VertexShader>> vertexShader;
	shared_ptr<Shader<ID3D11PixelShader>> pixelShader;
	shared_ptr<RasterizerState> rasterizerState;
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

public:
	// TODO : Setter
};

