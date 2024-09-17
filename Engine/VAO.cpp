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

void VAO::Create()
{
	glGenVertexArrays(1, &_id);
	glGenBuffers(1, &_vertex.GetID());
	glGenBuffers(1, &_color.GetID());
	glGenBuffers(1, &_index.GetID());

	glBindVertexArray(_id);

	// Vertex
	{
		int size = _vertex.GetBufferData().size() * sizeof(decltype(_vertex)::elementType);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex.GetID());
		glBufferData(
			GL_ARRAY_BUFFER,
			size,
			_vertex.GetBufferData().data(),
			GL_STATIC_DRAW
		);
	}

	// Index
	{
		int size = _index.GetBufferData().size() * sizeof(decltype(_index)::elementType);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index.GetID());
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			size,
			_index.GetBufferData().data(),
			GL_STATIC_DRAW
		);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// Color
	{
		int size = _color.GetBufferData().size() * sizeof(decltype(_color)::elementType);
		glBindBuffer(GL_ARRAY_BUFFER, _color.GetID());
		glBufferData(
			GL_ARRAY_BUFFER,
			size,
			_color.GetBufferData().data(),
			GL_STATIC_DRAW
		);
	}

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
}
