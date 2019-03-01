#version 330 core

layout (location = 0) in vec4 vertex;
uniform mat4 projection;
uniform vec2 translation;

out vec2 tex_coords;

void main()
{
    gl_Position = projection * vec4(vertex.xy + translation, 0.0, 1.0);
    tex_coords = vertex.zw;
}