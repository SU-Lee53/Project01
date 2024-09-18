#pragma once

// glm types are included here
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Global
{
	glm::mat4 view;
	glm::mat4 projection;
};

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

struct RGB
{
	union
	{
		struct
		{
			float r;
			float g;
			float b;
		};
		glm::vec3 rgb;
		float values[3];
	};

	operator glm::vec3()
	{
		return glm::vec3{ r,g,b };
	}
};

struct RGBA
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
		glm::vec4 rgba;
		float values[4];
	};
};

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

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