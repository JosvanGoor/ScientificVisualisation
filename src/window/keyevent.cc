#include "window.ih"

#include <iostream>

void Window::key_event(int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    switch(key)
    {
        case GLFW_KEY_H:
            print_shortcuts();
        break;

        case GLFW_KEY_C:
            set_colormapping
            ( 
                static_cast<ColorMapping>
                (
                    (static_cast<int>(d_colormapping) + 1) % 5
                )
            );
        break;

        case GLFW_KEY_R:
            set_drawmode
            (
                static_cast<DrawMode>
                (
                    (static_cast<int>(d_drawmode) + 1) % 2
                )
            );
        break;

        case GLFW_KEY_M:
            set_colormode
            (
                static_cast<ColorMode>
                (
                    (static_cast<int>(d_colormode) + 1) % 3
                )
            );
        break;

        case GLFW_KEY_S:
            set_scalingmode
            (
                static_cast<ScalingMode>
                (
                    (static_cast<int>(d_scalingmode) + 1) % 2
                )
            );
        break;

        case GLFW_KEY_MINUS:
            d_min -= 0.01;
        break;

        case GLFW_KEY_EQUAL:
            d_min = d_min + 0.01 > d_max ? d_max : d_min + 0.01;
        break;

        case GLFW_KEY_LEFT_BRACKET:
            d_max = d_max - 0.01 < d_min ? d_min : d_max - 0.01;
        break;

        case GLFW_KEY_RIGHT_BRACKET:
            d_max += 0.01;
        break;
    }
    print_settings();
}