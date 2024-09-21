#pragma once

template <ShaderType T>
class Shader
{
public:
	Shader(string file, const string& name, const string& version);
	~Shader();

public:
	void Create(string file, const string& name, const string& version);

public:
	ComPtr<T> GetComPtr() const { return _shader; }

private:
	wstring _filePath;
	ComPtr<T> _shader;
};

template<ShaderType T>
inline Shader<T>::Shader(string file, const string& name, const string& version)
	: _filePath(L"..\\Shader\\" + Utils::ToWString(file))
{
	Create(_filePath, name, version);
}

template<ShaderType T>
inline Shader<T>::~Shader()
{
}

template<ShaderType T>
inline void Shader<T>::Create(string file, const string& name, const string& version)
{
	SHADER->Create<T>(_filePath, name, version);
}
