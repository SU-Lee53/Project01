#pragma once

#include "Shader_Base.h"

class InputLayout;

class Shader
{
public:
	Shader();
	~Shader();

public:
	void Create();

public:
	shared_ptr<InputLayout> GetInputLayout() const { return _inputLayout; }
	shared_ptr<VertexShader> GetVertexShader() const { return _vs; }
	shared_ptr<PixelShader> GetPixelShader() const { return _ps; }


private:
	shared_ptr<InputLayout> _inputLayout;
	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;
};

