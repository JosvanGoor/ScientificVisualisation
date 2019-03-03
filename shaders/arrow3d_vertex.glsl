#version 330

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 position;
layout (location = 2) in float rotation;
layout (location = 3) in float scalar;

uniform mat4 projection;
const float PI = 3.1415926535897932384626433832795;

void main()
{
    float scale = max(0.0, min(1.0, scalar));

    vec3 pos;
    pos.x = vertex.x * cos(rotation) - vertex.y * sin(rotation);
    pos.y = vertex.y * cos(rotation) + vertex.x * sin(rotation);
    pos.z = vertex.z;
    pos = (pos * scale) + vec3(position, 0.0);

    gl_Position = projection * vec4(pos, 1.0);
}