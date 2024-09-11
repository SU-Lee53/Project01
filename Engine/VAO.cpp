#include "EnginePch.h"
#include "VAO.h"
#include "VBO.h"
#include "Shader.h"
VAO::VAO()
{
}

VAO::~VAO()
{
}

void VAO::MakeVAO(unsigned int shader)
{
	int bufferLocation = glGetUniformBlockIndex(shader, "VertexColor");


}
