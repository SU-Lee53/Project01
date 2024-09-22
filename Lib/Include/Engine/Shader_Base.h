#pragma once

template <ShaderType T>
class Shader_Base
{
public:
	Shader_Base() = default;
	Shader_Base(string file, const string& name, const string& version);
	~Shader_Base();

public:
	void Create(string file, const string& name, const string& version);

public:
	ComPtr<T> GetComPtr() const { return _shader; }

private:
	wstring _filePath;
	ComPtr<T> _shader;
};

template<ShaderType T>
inline Shader_Base<T>::Shader_Base(string file, const string& name, const string& version)
	: _filePath(L"..\\Shader\\" + Utils::ToWString(file))
{
	Create(_filePath, name, version);
}

template<ShaderType T>
inline Shader_Base<T>::~Shader_Base()
{
}

template<ShaderType T>
inline void Shader_Base<T>::Create(string file, const string& name, const string& version)
{
	SHADER->Create<T>(_filePath, name, version);
}


using VertexShader = Shader_Base<ID3D11VertexShader>;
using PixelShader = Shader_Base<ID3D11PixelShader>;