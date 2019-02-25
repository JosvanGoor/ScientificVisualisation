#version 330 core

layout (location = 0) in vec2 a_pos;
layout (location = 1) in vec2 a_col;

uniform mat4 u_transform;

out vec2 col;

void main()
{
    gl_Position = u_transform * vec4(a_pos.x, a_pos.y, 0.0, 1.0);
    col = a_col;
}