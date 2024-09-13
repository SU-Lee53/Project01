#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vColor;

out vec3 out_Color;

// uniform mat4 model;
// uniform mat4 projection;
// uniform mat4 view;

void main()
{
	gl_Position = vec4(vPos, 1.0f);

	out_Color = vec3(1.f, 0.f, 0.f);
}