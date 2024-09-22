#pragma once

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

private:
	wstring _filePath;
	string _name;
	string _version;

private:
	ComPtr<T> _shader;
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
	SHADER->Create<T>(_filePath, _name, _version);
}


using VertexShader = Shader_Base<ID3D11VertexShader>;
using PixelShader = Shader_Base<ID3D11PixelShader>;