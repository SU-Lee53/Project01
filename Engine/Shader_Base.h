#pragma once
#include "ShaderManager.h"
#include "Utils.h"

template <ShaderType T>
class Shader_Base
{
public:
	Shader_Base() = default;
	~Shader_Base();

public:
	void Create(const string& file, const string& name, const string& version);

public:
	ComPtr<T> GetComPtr() const { return _shader; }
	ComPtr<ID3DBlob> GetBlob() const { return _blob; }

	string GetName() const { return _name; }

private:
	wstring _filePath;
	string _name;
	string _version;

private:
	ComPtr<T> _shader;
	ComPtr<ID3DBlob> _blob;

public:
	using ShaderTy = T;
};

template<ShaderType T>
inline Shader_Base<T>::~Shader_Base()
{
}

template<ShaderType T>
inline void Shader_Base<T>::Create(const string& file, const string& name, const string& version)
{
	_filePath = L"..\\Shader\\" + Utils::ToWString(file);
	_name = name;
	_version = version;
	_shader = SHADER->Create<T>(_filePath, _name, _version, _blob);
}


using VertexShader = Shader_Base<ID3D11VertexShader>;
using PixelShader = Shader_Base<ID3D11PixelShader>;