#version 330 core

#define BLACKWHITE 0
#define RAINBOW 1
#define BANDS 2
#define SPACE 3
#define DUTCH 4

in float col;
out vec4 FragColor;
uniform int u_colormapping;
uniform vec2 u_limits;


float colormap_f1(float x) {
    return (0.3647 * x + 164.02) * x + 154.21;
}

float colormap_f2(float x) {
    return (126.68 * x + 114.35) * x + 0.1551;
}

float colormap_red(float x) {
    if (x < 0.0) {
        return 0.0;
    } else if (x < 0.136721748106749) {
        return colormap_f2(x) / 255.0;
    } else if (x < 0.23422409711017) {
        return (1789.6 * x - 226.52) / 255.0;
    } else if (x < 0.498842730309711) {
        return colormap_f1(x) / 255.0;
    } else if (x < 0.549121259378134) {
        return (-654.951781800243 * x + 562.838873112072) / 255.0;
    } else if (x < 1.0) {
        return ((3.6897 * x + 11.125) * x + 223.15) / 255.0;
    } else {
        return 237.0 / 255.0;
    }
}

float colormap_green(float x) {
    if (x < 0.0) {
        return 154.0 / 255.0;
    } else if (x < 3.888853260731947e-2) {
        return colormap_f1(x) / 255.0;
    } else if (x < 0.136721748106749e0) {
        return (-1455.86353067466 * x + 217.205447330541) / 255.0;
    } else if (x < 0.330799131955394) {
        return colormap_f2(x) / 255.0;
    } else if (x < 0.498842730309711) {
        return (1096.6 * x - 310.91) / 255.0;
    } else if (x < 0.549121259378134) {
        return colormap_f1(x) / 255.0;
    } else {
        return 244.0 / 255.0;
    }
}

float colormap_blue(float x) {
    if (x < 0.0) {
        return 93.0 / 255.0;
    } else if (x < 3.888853260731947e-2) {
        return (1734.6 * x + 93.133) / 255.0;
    } else if (x < 0.234224097110170) {
        return colormap_f1(x) / 255.0;
    } else if (x < 0.330799131955394) {
        return (-1457.96598791534 * x + 534.138211325166) / 255.0;
    } else if (x < 0.549121259378134) {
        return colormap_f2(x) / 255.0;
    } else if (x < 1.0) {
        return ((3.8931 * x + 176.32) * x + 3.1505) / 255.0;
    } else {
        return 183.0 / 255.0;
    }
}

vec4 colormap(float col)
{
    col = max(min(col,u_limits.y),u_limits.x);
    col = (col - u_limits.x) / (u_limits.y - u_limits.x);

    if (u_colormapping == BLACKWHITE)
        return vec4(col, col, col, 1.0f);

    if (u_colormapping == SPACE)
        return vec4(colormap_red(col), colormap_green(col), colormap_blue(col), 1.0);

    if (u_colormapping == DUTCH)
        return vec4
        (
            max(0.0f, min(1.0f, 2 * col)),
            max(0.0f, min(1.0f, 1 - abs(-1 + 2 * col))),
            max(0.0f, min(1.0f, 2.0 - 2 * col)),
            1.0f
        );

    if (u_colormapping == BANDS)
    {
        const int NLEVELS = 7;
        //col += (u_limits.y / NLEVELS) * 0.5;
        col *= NLEVELS + 1;
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