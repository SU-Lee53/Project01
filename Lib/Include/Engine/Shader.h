#pragma once

class Shader
{
public:
	Shader(wstring vsName, wstring fsName);
	~Shader();

public:
	void LoadShaderFiles();

private:
	void LoadVertexShader();
	void LoadFragMentShader();

private:
	void LoadShaderImpl(wstring path, OUT unsigned int& id);

private:
	wstring _vsName;
	wstring _fsName;

	unsigned int _vsId;
	unsigned int _fsId;

private:
	wstring _shaderPath = L"../Shader/";
	wstring _glsl = L".glsl";
};

