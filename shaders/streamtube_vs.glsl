#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec3 fs_normal;
uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex, 1.0);
    fs_normal = (normal + 0.5) / 2;
}