#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;

out vec3 color;

uniform mat4 u_matrix;

void main()
{
    color = a_color;
    gl_Position = u_matrix * vec4(a_position, 1);
}