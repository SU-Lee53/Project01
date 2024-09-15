#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vColor;

layout (std140) uniform Input
{
	vec3 pos;
	vec3 color;
	mat4 world;
};

out vec3 out_Color;

layout (std140) uniform Global
{
	mat4 view;
	mat4 projection;
};

void main()
{
	gl_Position = vec4(vPos, 1.0f);

	out_Color = vColor;
}