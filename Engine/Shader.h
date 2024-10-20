#pragma once

#include "Shader_Base.h"

class InputLayout;

class Shader
{
public:
	Shader();
	~Shader();

public:
	void CreateDefault();

	void CreateVertexShader(const string& fileName, const string& shaderName);
	void CreatePixelShader(const string& filename, const string& shaderName);
	
	// explicitly used when override inputlayout
	void CreateInputLayout();


public:
	void SetVertexShader(shared_ptr<VertexShader> shader) { _vs = shader; CreateInputLayout(); }
	void SetPixelShader(shared_ptr<PixelShader> shader) { _ps = shader; }

	shared_ptr<InputLayout> GetInputLayout() const { return _inputLayout; }
	shared_ptr<VertexShader> GetVertexShader() const { return _vs; }
	shared_ptr<PixelShader> GetPixelShader() const { return _ps; }


private:
	shared_ptr<InputLayout> _inputLayout;
	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;
};
