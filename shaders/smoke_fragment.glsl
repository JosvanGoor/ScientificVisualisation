#version 330 core

#define BLACKWHITE 0
#define RAINBOW 1
#define BANDS 2

in float col;
out vec4 FragColor;
uniform int u_colormapping;

vec4 colormap(float col)
{
    if (u_colormapping == BLACKWHITE)
        return vec4(col, col, col, 1.0f);

    if (u_colormapping == BANDS)
    {
        const int NLEVELS = 7;
        col *= NLEVELS;
        col = int(col);
        col /= NLEVELS;
    }

    const float dx = 0.8;

    col = max(min(col, 1), 0);
    col = (6 - 2 * dx) * col + dx;

    return vec4
    (
        max(0.0f, (3 - abs(col - 4) - abs(col - 5)) / 2),
        max(0.0f, (4 - abs(col - 2) - abs(col - 4)) / 2),
        max(0.0f, (3 - abs(col - 1) - abs(col - 2)) / 2),
        1.0f
    );
}

void main()
{
    FragColor = colormap(col);
} 