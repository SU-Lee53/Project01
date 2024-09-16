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
	LoadShaderImpl<SHADER_TYPE::VERTEX>(_vsName, _vsId);
}

void Shader::LoadFragMentShader()
{
	LoadShaderImpl<SHADER_TYPE::FRAGMENT>(_fsName, _fsId);
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

unsigned int Shader::GetUniformBlockLocation(string name)
{
	return glGetUniformBlockIndex(_shaderId, name.c_str());
}

unsigned int Shader::GetUniformLocation(string name)
{
	return glGetUniformLocation(_shaderId, name.c_str());
}
