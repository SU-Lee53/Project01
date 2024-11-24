#include "EnginePch.h"
#include "Pipeline.h"

Pipeline::Pipeline()
{
}

Pipeline::~Pipeline()
{
}

void Pipeline::Update(PipelineDesc desc)
{
	DC->IASetInputLayout(desc.inputLayout->GetComPtr().Get());
	DC->IASetPrimitiveTopology(desc.topology);

	// Fill Pipelines (IA - VS - RS - PS - OM)

    if (desc.vertexShader)
        DC->VSSetShader(desc.vertexShader->GetComPtr().Get(), nullptr, 0);

    if (desc.rasterizerState)
        DC->RSSetState(desc.rasterizerState->GetComPtr().Get());

    if (desc.pixelShader)
        DC->PSSetShader(desc.pixelShader->GetComPtr().Get(), nullptr, 0);

    if (desc.blendState)
        DC->OMSetBlendState(desc.blendState->GetComPtr().Get(), desc.blendState->GetBlendFactor(), desc.blendState->GetSampleMask());
}

void Pipeline::SetVertexBuffer(shared_ptr<VertexBuffer> buffer)
{
    uint32 stride = buffer->GetStride();
    uint32 offset = buffer->GetOffset();
    DC->IASetVertexBuffers(0, 1, buffer->GetComPtr().GetAddressOf(), &stride, &offset);
}

void Pipeline::SetIndexBuffer(shared_ptr<IndexBuffer> buffer)
{
    uint32 stride = buffer->GetStride();
    uint32 offset = buffer->GetOffset();
    DC->IASetIndexBuffer(buffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
}

void Pipeline::SetRasterizerState(shared_ptr<RasterizerState> rs)
{
    DC->RSSetState(rs->GetComPtr().Get());
}

void Pipeline::DrawIndexed(uint32 indexCount, uint32 startIndexLocation, uint32 baseVertexLocation)
{
    DC->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
}
