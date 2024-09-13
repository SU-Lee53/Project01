#include "EnginePch.h"
#include "Shader.h"

Shader::Shader(wstring vsName, wstring fsName)
{
	_vsName = _shaderPath + vsName + _glsl;
	_fsName = _shaderPath + fsName + _glsl;
	MakeShaderProgram();
}

Shader::~Shader()
{
}

void Shader::MakeShaderProgram()
{
	LoadVertexShader();
	LoadFragMentShader();
	LinkShader();
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

	id = glCreateShader(GL_VERTEX_SHADER);
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

void Shader::LinkShader()
{
	_shaderId = glCreateProgram();
	
	glAttachShader(_shaderId, _vsId);
	glAttachShader(_shaderId, _fsId);

	glLinkProgram(_shaderId);

	glDeleteShader(_vsId);
	glDeleteShader(_fsId);

	int result;
	char errorLog[512];
	glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(_shaderId, 512, NULL, errorLog);
		cerr << "Error: Failed to Link shader" << errorLog << endl;
		return;
	}
	else
	{
		cout << "Link Success" << endl;
	}
}
