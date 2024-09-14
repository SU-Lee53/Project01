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

void VAO::MakeVAO()
{
	glGenVertexArrays(1, &_id);
	glGenBuffers(1, &_vertex.GetID());
	glGenBuffers(1, &_color.GetID());
	glGenBuffers(1, &_index.GetID());

	glBindVertexArray(_id);

	// Vertex
	{
		int size = _vertex.GetBuffer().size() * sizeof(decltype(_vertex)::elementType);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex.GetID());
		glBufferData(
			GL_ARRAY_BUFFER,
			size,
			_vertex.GetBuffer().data(),
			GL_STATIC_DRAW
		);
	}

	// Index
	{
		int size = _index.GetBuffer().size() * sizeof(decltype(_index)::elementType);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index.GetID());
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			size,
			_index.GetBuffer().data(),
			GL_STATIC_DRAW
		);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// Color
	{
		int size = _color.GetBuffer().size() * sizeof(decltype(_color)::elementType);
		glBindBuffer(GL_ARRAY_BUFFER, _color.GetID());
		glBufferData(
			GL_ARRAY_BUFFER,
			size,
			_color.GetBuffer().data(),
			GL_STATIC_DRAW
		);
	}

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}
