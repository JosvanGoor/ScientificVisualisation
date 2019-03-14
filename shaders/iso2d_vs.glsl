#version 330

layout (location = 0) in vec2 vertex;

uniform vec3 color;
uniform mat4 projection;

out vec3 fs_color;

void main()
{
    fs_color = color;
    gl_Position = projection * vec4(vertex, 0.0, 1.0);
}