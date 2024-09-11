#pragma once
#include "VBO.h"

class VAO
{
public:
	VAO();
	~VAO();

	void MakeVAO(unsigned int shader);

public:
	VBO& GetVBO() { return _vbo; }

private:
	unsigned int id;
	VBO _vbo;
};

