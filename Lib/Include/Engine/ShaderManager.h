#pragma once
#include "Manager.h"

template <typename C>
concept IsShaderType = requires(C c)
{
	same_as<C, ID3D11VertexShader>			or
		same_as<C, ID3D11HullShader>		or
		same_as<C, ID3D11DomainShader>		or
		same_as<C, ID3D11GeometryShader>	or
		same_as<C, ID3D11PixelShader>		or
		same_as<C, ID3D11ComputeShader>;
};

template <typename C>
concept ShaderType = IsShaderType<C>;
	
class ShaderManager : public Manager_Base
{
public:
	ShaderManager();
	virtual ~ShaderManager();

public:
	virtual void Init() override;

	template <ShaderType T>
	ComPtr<T> Create(const wstring& path, const string& name, const string& version);

private:
	void LoadFromFile(const wstring& path, const string& name, const string& version);

private:
	ComPtr<ID3DBlob> _blob;
public:
	constexpr static  MANAGER_TYPE ty = MANAGER_TYPE::Shader;
};

template <ShaderType T>
inline ComPtr<T> ShaderManager::Create(const wstring& path, const string& name, const string& version)
{
	LoadFromFile(path, name, version);

	ComPtr<T> shader;
	HRESULT hr;

	if constexpr (is_same_v<T, ID3D11VertexShader>)
	{
		hr = DEVICE->CreateVertexShader(
			_blob->GetBufferPointer(),
			_blob->GetBufferSize(),
			nullptr,
			shader.GetAddressOf()
		);
	}
	else if constexpr (is_same_v<T, ID3D11PixelShader>)
	{
		hr = DEVICE->CreatePixelShader(
			_blob->GetBufferPointer(),
			_blob->GetBufferSize(),
			nullptr,
			shader.GetAddressOf()
		);
	}
	else
	{
		assert(false);
	}

	HR_ASSERT(hr);

	return shader;
}
