#version 330 core


in vec3 fs_normal;
out vec4 frag_color;

void main()
{
    frag_color = vec4(fs_normal, 1.0);
}