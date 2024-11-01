#pragma once
#include "Utils.h"

template <typename C>
concept IsShaderType = requires(C c)
{
	same_as<C, ID3D11VertexShader> or
		same_as<C, ID3D11HullShader> or
		same_as<C, ID3D11DomainShader> or
		same_as<C, ID3D11GeometryShader> or
		same_as<C, ID3D11PixelShader> or
		same_as<C, ID3D11ComputeShader>;
};

template <typename C>
concept ShaderType = IsShaderType<C>;

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

	friend class hash<Shader_Base<ID3D11VertexShader>>;
	friend class hash<Shader_Base<ID3D11PixelShader>>;

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

namespace std
{
	template<>
	struct hash<VertexShader>
	{
		size_t operator()(const VertexShader& vs) const
		{
			hash<string> hash_func;
			return hash_func(vs._name);
		}
	};

	template<>
	struct hash<PixelShader>
	{
		size_t operator()(const PixelShader& ps) const
		{
			hash<string> hash_func;
			return hash_func(ps._name);
		}
	};
}
