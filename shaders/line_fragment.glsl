#version 330 core

#define BLACKWHITE 0
#define RAINBOW 1
#define BANDS 2

in vec2 col;
out vec4 FragColor;
uniform int u_colormapping;

const float PI = 3.1415926535897932384626433832795;

vec4 direction_to_color(vec2 col)
{
    if (u_colormapping == BLACKWHITE)
        return vec4(1.0f, 1.0f, 1.0f, 1.0f);

    float f = atan(col.y, col.x) / PI + 1;

    float r = f;
    r = r > 1 ? 2 - r : r;

    float g = f + (2.0f / 3.0f);
    g = g > 2 ? g - 2 : g;
    g = g > 1 ? 2 - g : g;

    float b = f + 2.0f * (2.0f / 3.0f);
    b = b > 2 ? b - 2 : b;
    b = b > 1 ? 2 - b : b;

    return vec4(r, g, b, 1.0f);
}

void main()
{
    FragColor = direction_to_color(col);
} 