#version 330 core

layout (location = 0) in vec2 a_pos;
layout (location = 1) in float a_height;
layout (location = 2) in float a_col;

uniform vec2 heightlim = vec2(0.0, 1.0);
uniform mat4 projection;

out float col;

void main()
{
    float hght = max(min(a_height, heightlim.y), heightlim.x);
    hght = (hght - heightlim.x) / (heightlim.y - heightlim.x);

    gl_Position = projection * vec4(a_pos.x, a_pos.y, hght, 1.0);
    col = a_col;
}