#pragma once

// glm types are included here
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Color
{
	union
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		};
		glm::vec4 rgb;
		float values[4];
	};
};

struct Pos2D
{
	union
	{
		struct
		{
			float x;
			float y;
		};
		glm::vec2 xy;
		float values[2];
	};
};

struct Pos3D
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		glm::vec2 xyz;
		float values[3];
	};
};