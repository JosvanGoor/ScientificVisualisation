#version 330

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 position;
layout (location = 2) in float rotation;

uniform mat4 projection;

const float PI = 3.1415926535897932384626433832795;

mat4 rotation_mat(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

void main()
{
    vec2 pos;
    pos.x = vertex.x * cos(rotation) - vertex.y * sin(rotation);
    pos.y = vertex.y * cos(rotation) + vertex.x * sin(rotation);
    gl_Position = projection * vec4(pos + position, 0.0, 1.0);
}