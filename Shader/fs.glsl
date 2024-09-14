#version 330 core

uniform vec3 out_Color;
out vec4 fragColor;

void main()
{
	fragColor = vec4(out_Color, 1.0f);
}