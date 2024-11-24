#pragma once

struct PipelineDesc
{
	shared_ptr<InputLayout> inputLayout;
	shared_ptr<VertexShader> vertexShader;
	shared_ptr<PixelShader> pixelShader;
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

	template <ShaderType shaderTy>
	void SetTexture(uint32 slot, shared_ptr<Texture> texture);
	
	template <ShaderType shaderTy>
	void SetSamplerState(uint32 slot, shared_ptr<SamplerState> samplerState);

	void SetRasterizerState(shared_ptr<RasterizerState> rs);

	template <typename T, ShaderType shaderTy>
	void SetConstantBuffer(shared_ptr<ConstantBuffer<T>> buffer);
	
	void DrawIndexed(uint32 indexCount, uint32 startIndexLocation, uint32 baseVertexLocation);

};

template<ShaderType shaderTy>
inline void Pipeline::SetTexture(uint32 slot, shared_ptr<Texture> texture)
{
	if constexpr (is_same_v<shaderTy, VertexShader>)
	{
		DC->VSSetShaderResources(slot, 1, texture->GetComPtr().GetAddressOf());
	}
	else if constexpr (is_same_v<shaderTy, PixelShader>)
	{
		DC->PSSetShaderResources(slot, 1, texture->GetComPtr().GetAddressOf());
	}
	else
		assert(false);
}

template<ShaderType shaderTy>
inline void Pipeline::SetSamplerState(uint32 slot, shared_ptr<SamplerState> samplerState)
{
	if constexpr (is_same_v<shaderTy, VertexShader>)
	{
		DC->VSSetSamplers(slot, 1, samplerState->GetComPtr().GetAddressOf());
	}
	else if constexpr (is_same_v<shaderTy, PixelShader>)
	{
		DC->PSSetSamplers(slot, 1, samplerState->GetComPtr().GetAddressOf());
	}
	else
		assert(false);
}

template<typename T, ShaderType shaderTy>
inline void Pipeline::SetConstantBuffer(shared_ptr<ConstantBuffer<T>> buffer)
{
	if constexpr (is_same_v<shaderTy, VertexShader>)
	{
		DC->VSSetConstantBuffers(T::slot, 1, buffer->GetComPtr().GetAddressOf());
	}
	else if constexpr (is_same_v<shaderTy, PixelShader>)
	{
		DC->PSSetConstantBuffers(T::slot, 1, buffer->GetComPtr().GetAddressOf());
	}
	else
		assert(false);

}
