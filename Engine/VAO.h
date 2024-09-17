#pragma once
#include "VBO.h"

class VAO
{
public:
	VAO();
	~VAO();

	void Create();

public:
	template <BUFFER_TYPE ty>
	constexpr auto& GetVBO()
	{
		if constexpr (ty == BUFFER_TYPE::Vertex)
			return _vertex;
		else if constexpr (ty == BUFFER_TYPE::Color)
			return _color;
		else if constexpr (ty == BUFFER_TYPE::Index)
			return _index;
	}

	unsigned int GetID() { return _id; }

private:
	unsigned int _id;

	VBO<float, BUFFER_TYPE::Vertex> _vertex;
	VBO<float, BUFFER_TYPE::Color> _color;
	VBO<unsigned int, BUFFER_TYPE::Index> _index;
	
};

