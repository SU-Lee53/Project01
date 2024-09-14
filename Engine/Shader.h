#pragma once

enum class SHADER_TYPE
{
	VERTEX = 0,
	FRAGMENT
};

class Shader
{
public:
	Shader(wstring vsName, wstring fsName);
	~Shader();

public:
	void MakeShaderProgram();

private:
	void LoadVertexShader();
	void LoadFragMentShader();

private:
	template <SHADER_TYPE Ty>
	void LoadShaderImpl(wstring path, OUT unsigned int& id);

private:
	void LinkShader();

public:
	unsigned int GetID() { return _shaderId; }

private:
	unsigned int _shaderId;

private:
	wstring _vsName;
	wstring _fsName;

	unsigned int _vsId;
	unsigned int _fsId;

private:
	wstring _shaderPath = L"../Shader/";
	wstring _glsl = L".glsl";
};

template<SHADER_TYPE Ty>
inline void Shader::LoadShaderImpl(wstring path, OUT unsigned int& id)
{
	auto p = filesystem::path(path);

	ifstream is(p);
	if (!is.is_open())
		assert(false);

	string temp = Utils::FileToBuf(is);
	const char* buf = temp.c_str();

	if constexpr (Ty == SHADER_TYPE::VERTEX)
		id = glCreateShader(GL_VERTEX_SHADER);

	else if constexpr (Ty == SHADER_TYPE::FRAGMENT)
		id = glCreateShader(GL_FRAGMENT_SHADER);
	else
		assert(false);

	glShaderSource(id, 1, &buf, NULL);
	glCompileShader(id);

	int result;
	char errorLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(id, 512, NULL, errorLog);
		cerr << "Error: Failed to compile shader" << errorLog;
		cout << "FileName = " << Utils::ToString(path) << endl;

		return;
	}
	else
	{
		cout << Utils::ToString(path) << " Compile Success" << endl;
	}

}
