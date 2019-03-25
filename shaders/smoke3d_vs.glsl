#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_norm;
layout (location = 2) in vec2 a_tex;

uniform mat4 projection;

out vec3 fs_position;
out vec3 fs_normal;
out vec2 fs_texcoord;

void main()
{
    gl_Position = projection * vec4(a_pos, 1.0);
    fs_position = a_pos;
    fs_texcoord = a_tex;
    fs_normal = a_norm;
}