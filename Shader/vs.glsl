#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vColor;
out vec3 out_Color;

//layout (std140) uniform Global
//{
//	mat4 view;
//	mat4 projection;
//};

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = world * vec4(vPos, 1.0f);

	out_Color = vColor;
}