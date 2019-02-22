#include "window.ih"

Color Window::direction_to_color(float x, float y)
{
    if (!d_color_direction)
    {
        return Color{1, 1, 1};
    }

    float f = atan2(y, x) / M_PI + 1;
    
    float r = f;
    if (r > 1.0f)
        r = 2 - r;

    float g = f + (2.0f/3.0f);
    if (g > 2)
        g -= 2;
    if (g > 1)
        g = 2 - g;

    float b = f + 2 * (2.0f / 3.0f);
    if (b > 2)
        b -= 2;
    if (b > 1)
        b = 2 - b;

    return Color{r, g, b};
}