#pragma once
#include "Manager.h"
#include "Shader_Base.h"

enum class SHADER_TYPE
{
	Vertex = 0,
	Hull,
	Domain,
	Geometry,
	Pixel,
	Compute
};

class Shader;

struct SHADER_DESC
{
	SHADER_TYPE type;
	string fileName;
	string entryName;
};

class ShaderManager : public Manager_Base
{
public:
	ShaderManager();
	virtual ~ShaderManager();

public:
	virtual void Init() override;

	template <ShaderType T>
	ComPtr<T> Create(const wstring& path, const string& name, const string& version, OUT ComPtr<ID3DBlob>& blob);

private:
	void LoadFromFile(const wstring& path, const string& name, const string& version, OUT ComPtr<ID3DBlob>& blob);

public:
	constexpr static  MANAGER_TYPE ty = MANAGER_TYPE::Shader;

	static vector<SHADER_DESC> descs;

	unordered_set<VertexShader> _vsSet;
	unordered_set<PixelShader> _psSet;

};

template <ShaderType T>
inline ComPtr<T> ShaderManager::Create(const wstring& path, const string& name, const string& version, OUT ComPtr<ID3DBlob>& blob)
{
	LoadFromFile(path, name, version, blob);

	ComPtr<T> shader;
	HRESULT hr;

	if constexpr (is_same_v<T, ID3D11VertexShader>)
	{
		hr = DEVICE->CreateVertexShader(
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			nullptr,
			shader.GetAddressOf()
		);
	}
	else if constexpr (is_same_v<T, ID3D11PixelShader>)
	{
		hr = DEVICE->CreatePixelShader(
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
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
