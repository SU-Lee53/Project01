#pragma once

#include "Shader_Base.h"

class InputLayout;

class Shader
{
public:
	Shader();
	~Shader();

public:
	void Init();

private:
	shared_ptr<InputLayout> _inputLayout;
	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;
};

