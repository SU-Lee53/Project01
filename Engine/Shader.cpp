#include "EnginePch.h"
#include "Shader.h"
#include "InputLayout.h"
#include "InputData.h"
#include "Shader_Base.h"

Shader::Shader()
{
	// For Test
	CreateDefault();
}

Shader::~Shader()
{
}

void Shader::CreateDefault()
{
	_vs = make_shared<VertexShader>();
	_ps = make_shared<PixelShader>();

	_vs->Create("Vertex.hlsl", "VS", "vs_5_0");
	_ps->Create("PixelWithNormal.hlsl", "PS", "ps_5_0");

	_inputLayout = make_shared<InputLayout>();
	_inputLayout->Create(VertexType::descs, _vs->GetBlob());

}

void Shader::CreateVertexShader(const string& fileName, const string& shaderName, vector<D3D11_INPUT_ELEMENT_DESC> desc)
{
	if (_vs == nullptr)
		_vs = make_shared<VertexShader>();
		
	_vs->Create(fileName, shaderName, "vs_5_0");

	CreateInputLayout(desc);
}

void Shader::CreatePixelShader(const string& fileName, const string& shaderName)
{
	if (_ps == nullptr)
		_ps = make_shared<PixelShader>();

	_ps->Create(fileName, shaderName, "ps_5_0");
}

void Shader::CreateInputLayout(vector<D3D11_INPUT_ELEMENT_DESC> desc)
{
	if(_inputLayout == nullptr)
		_inputLayout = make_shared<InputLayout>();

	_inputLayout->Create(desc, _vs->GetBlob());
}
