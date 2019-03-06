#version 330

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

layout (location = 3) in vec2 position;
layout (location = 4) in float rotation;
layout (location = 5) in float scalar;

uniform mat4 projection;
const float PI = 3.1415926535897932384626433832795;

out vec3 g_normal;
out vec3 g_position;

mat4 position_transform()
{
    return mat4
    (
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        position.x, position.y, 0, 1
    );
}

mat4 scale_transform()
{
    float scale = 0.75 * max(0.0, min(1.0, scalar));
    return mat4
    (
        scale, 0, 0, 0,
        0, scale, 0, 0,
        0, 0, scale, 0,
        0, 0, 0, 1
    );
}

mat4 rotation_transform()
{
    return mat4
    (
        cos(rotation), sin(rotation), 0, 0,
        sin(rotation), -cos(rotation), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

void main()
{
    mat4 M = position_transform() *
             scale_transform() *
             rotation_transform();

    mat3 norm_transform = transpose(inverse(mat3(M)));
    g_normal = norm_transform * normal;
    g_position = (M * vec4(vertex, 1.0)).xyz;

    gl_Position = projection * M * vec4(vertex, 1.0);
}