#version 330 core

in uniform VertexColor
{
    vec3 pos;
    vec3 color;
}

in uniform Global
{
    mat4 View;
    mat4 Projection;
    mat4 VP;
}

in uniform World
{
    mat4 World
}
