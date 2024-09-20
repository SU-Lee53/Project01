#include "EnginePch.h"
#include "Pipeline.h"
#include "InputLayout.h"
#include "Shader.h"
#include "RasterizerState.h"
#include "SamplerState.h"
#include "BlendState.h"

Pipeline::Pipeline()
{
}

Pipeline::~Pipeline()
{
}

void Pipeline::Update(PipelineDesc desc)
{
	//DC->IASetInputLayout(desc.inputLayout->GetComPtr().Get());
	//DC->IASetPrimitiveTopology(desc.topology);

	// TODO : Fill Pipelines (IA - VS - RS - PS - OM)
}
