#include "EnginePch.h"
#include "Shader.h"
#include "InputLayout.h"


Shader::Shader()
{
}

Shader::~Shader()
{
}

void Shader::Init()
{
	D3D11_INPUT_ELEMENT_DESC desc;
	memset(&desc, 0, sizeof(desc));
	{
		// TODO : Fill
	}

	_inputLayout = make_shared<InputLayout>();



	_vs = make_shared<VertexShader>();
	_ps = make_shared<PixelShader>();

	_vs->Create("test.hlsl", "VS", "vs_5_0");
	_ps->Create("test.hlsl", "PS", "ps_5_0");
}
