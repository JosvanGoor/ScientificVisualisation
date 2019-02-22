#include "window.ih"

Color Window::colormap(float col)
{
    const int NLEVELS = 7; //?

    switch(d_colormapping)
    {
        case ColorMapping::BLACKWHITE:
            return Color {col, col, col};
        break;

        case ColorMapping::BANDS:
            col *= NLEVELS;
            col = static_cast<int>(col);
            col /= NLEVELS;
            //fallthrough
        case ColorMapping::RAINBOW:
        {
            const float dx = 0.8; //??
            if (col < 0) col = 0;
            if (col > 1) col = 1;
            col = (6 - 2 * dx) * col + dx;

            return Color
            {
                max(0.0f, (3 - fabs(col - 4) - fabs(col - 5)) / 2),
                max(0.0f, (4 - fabs(col - 2) - fabs(col - 4)) / 2),
                max(0.0f, (3 - fabs(col - 1) - fabs(col - 2)) / 2)
            };
        }
        break;
    }

    return Color{1, 1, 1};
}