#include "window.ih"

#include <iostream>

void Window::key_event(int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    switch(key)
    {
        case GLFW_KEY_Q:
            glfwSetWindowShouldClose(d_window, true);
        break;

        case GLFW_KEY_H:
            print_shortcuts();
        break;

        case GLFW_KEY_C:
            set_colormapping(rotate_enum(d_colormapping));
        break;

        case GLFW_KEY_D:
            set_divmode(rotate_enum(d_divmode));
        break;

        case GLFW_KEY_R:
            set_drawmode(rotate_enum(d_drawmode));
        break;

        case GLFW_KEY_M:
            set_colormode(rotate_enum(d_colormode));
        break;

        case GLFW_KEY_S:
            set_scalingmode(rotate_enum(d_scalingmode));
        break;

        case GLFW_KEY_G:
            cout <<"test\n";
            set_glyphmode(rotate_enum(d_glyphmode));
            cout << glyphmode_string(d_glyphmode) << '\n';
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
}