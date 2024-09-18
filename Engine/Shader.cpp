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

void Shader::SetBool(const string& name, const bool value)
{
	glUniform1i(glGetUniformLocation(_shaderId, name.c_str()), (int)value);
}

void Shader::SetInt(const string& name, const int value)
{
	glUniform1i(glGetUniformLocation(_shaderId, name.c_str()), value);
}

void Shader::Setfloat(const string& name, const float value)
{
	glUniform1f(glGetUniformLocation(_shaderId, name.c_str()), value);
}

void Shader::SetVec3(const string& name, const glm::vec3 value)
{
	glUniform3fv(glGetUniformLocation(_shaderId, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetVec4(const string& name, const glm::vec4 value)
{
	glUniform4fv(glGetUniformLocation(_shaderId, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetMat3(const string& name, const glm::mat3 value)
{
	glUniformMatrix3fv(glGetUniformLocation(_shaderId, name.c_str()),1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat4(const string& name, const glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(_shaderId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

unsigned int Shader::GetUniformBlockLocation(string name)
{
	return glGetUniformBlockIndex(_shaderId, name.c_str());
}

unsigned int Shader::GetUniformLocation(string name)
{
	return glGetUniformLocation(_shaderId, name.c_str());
}
