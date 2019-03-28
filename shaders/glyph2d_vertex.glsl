#version 330

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec3 position;
layout (location = 2) in float rotation;
layout (location = 3) in float incolor;

out float color;

uniform mat4 projection;

const float PI = 3.1415926535897932384626433832795;

void main()
{
    vec2 pos;
    float scale = 1.0;
    pos.x = (vertex.x * cos(rotation) - vertex.y * sin(rotation)) * min(scale, 1.0f);
    pos.y = (vertex.y * cos(rotation) + vertex.x * sin(rotation)) * min(scale, 1.0f);
    gl_Position = projection * vec4(pos + position.xy, position.z, 1.0);
    color = incolor;
}