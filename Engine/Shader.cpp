#include "EnginePch.h"
#include "Shader.h"

Shader::Shader(wstring filename)
	: _filePath(L"..\\Shader\\" + filename)
{
}

Shader::~Shader()
{
}

void Shader::Create()
{
	CreateVertexShader();
	CreatePixelShader();
}

void Shader::LoadFromFile(const string& name, const string& version)
{
	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

	HRESULT hr = D3DCompileFromFile(
		_filePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		_blob.GetAddressOf(),
		nullptr
	);

	HR_ASSERT(hr);
}


void Shader::CreateVertexShader()
{
	LoadFromFile("VS", "vs_5_0");

	HRESULT hr = DEVICE->CreateVertexShader(
		_blob->GetBufferPointer(),
		_blob->GetBufferSize(),
		nullptr,
		_vs.GetAddressOf()
	);

	HR_ASSERT(hr);
}

void Shader::CreatePixelShader()
{
	LoadFromFile("PS", "ps_5_0");

	HRESULT hr = DEVICE->CreatePixelShader(
		_blob->GetBufferPointer(),
		_blob->GetBufferSize(),
		nullptr,
		_ps.GetAddressOf()
	);

	HR_ASSERT(hr);
}
