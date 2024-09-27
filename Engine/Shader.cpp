#include "EnginePch.h"
#include "Shader.h"
#include "InputLayout.h"
#include "InputData.h"

Shader::Shader()
{
}

Shader::~Shader()
{
}

void Shader::Create()
{
	_vs = make_shared<VertexShader>();
	_ps = make_shared<PixelShader>();

	_vs->Create("test.hlsl", "VS", "vs_5_0");
	_ps->Create("test.hlsl", "PS", "ps_5_0");

	_inputLayout = make_shared<InputLayout>();
	_inputLayout->Create(VertexColorData::descs, _vs->GetBlob());

}
