#version 330 core

uniform sampler2D tex;

in vec2 fs_texcoord;
// in vec3 fs_normal;
out vec4 FragColor;


void main()
{
    // FragColor = vec4(fs_texcoord, 0.0, 1.0);
    FragColor = texture(tex, fs_texcoord);
}