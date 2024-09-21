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
