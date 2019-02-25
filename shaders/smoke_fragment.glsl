#version 330 core

in float col;
out vec4 FragColor;

vec4 colormap(float col)
{
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