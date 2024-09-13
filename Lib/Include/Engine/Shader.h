#pragma once

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

