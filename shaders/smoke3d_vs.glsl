#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_norm;
layout (location = 2) in float a_col;

uniform mat4 projection;

out vec3 normal;
out float col;


void main()
{
    gl_Position = projection * vec4(a_pos, 1.0);
    col = a_col;
    normal = a_norm;
}