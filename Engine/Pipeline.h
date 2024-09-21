#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

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
	void SetVertexBuffer(shared_ptr<VertexBuffer> buffer);
	void SetIndexBuffer(shared_ptr<IndexBuffer> buffer);

	void SetSamplerState(uint32 slot, uint32 scope, shared_ptr<SamplerState> samplerState);

	template <typename T, ShaderType shaderTy>
	void SetConstantBuffer(uint32 slot, shared_ptr<ConstantBuffer<T>> buffer);
	
};

template<typename T, ShaderType shaderTy>
inline void Pipeline::SetConstantBuffer(uint32 slot, shared_ptr<ConstantBuffer<T>> buffer)
{
	if constexpr (is_same_v<shaderTy, id3d11)

}
