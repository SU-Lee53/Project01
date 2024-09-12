#include "EnginePch.h"
#include "Shader.h"

Shader::Shader(wstring vsName, wstring fsName)
{
	_vsName = _shaderPath + vsName + _glsl;
	_fsName = _shaderPath + fsName + _glsl;
	LoadShaderFiles();
}

Shader::~Shader()
{
}

void Shader::LoadShaderFiles()
{
	LoadVertexShader();
	LoadFragMentShader();
}

void Shader::LoadVertexShader()
{
	LoadShaderImpl(_vsName, _vsId);
}

void Shader::LoadFragMentShader()
{
	LoadShaderImpl(_fsName, _fsId);
}

void Shader::LoadShaderImpl(wstring path, OUT unsigned int& id)
{
	auto p = filesystem::path(path);

	ifstream is(p);
	if (!is.is_open())
		assert(false);

	string temp = Utils::FileToBuf(is);
	const char* buf = temp.c_str();

	cout << buf << endl;

	id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(id, 1, &buf, NULL);
	glCompileShader(id);

	int result;
	char errorLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(id, 512, NULL, errorLog);
		cerr << "Error: Failed to compile shader" << errorLog << endl;
		cout << "FileName = " << Utils::ToString(path) << endl;

		return;
	}
	else
	{
		cout << "Shader Compile Success" << endl;
		cout << "FileName = " << Utils::ToString(path) << endl;
	}
}
