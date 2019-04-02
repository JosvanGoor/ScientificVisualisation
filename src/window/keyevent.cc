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
            d_help = !d_help;
        break;

        case GLFW_KEY_I:
            set_isomode(rotate_enum(d_isomode));
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
            if (mods & GLFW_MOD_SHIFT)
                set_heightmode(rotate_enum(d_heightmode));
            else
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
            if (mods & GLFW_MOD_SHIFT)
                d_min -= 0.01;
            else
                d_max = d_max - 0.01 < d_min ? d_min : d_max - 0.01;
        break;

        case GLFW_KEY_EQUAL:
            if (mods & GLFW_MOD_SHIFT)
                d_min = d_min + 0.01 > d_max ? d_max : d_min + 0.01;
            else 
                d_max += 0.01;
        break;

        case GLFW_KEY_COMMA:
            if (mods & GLFW_MOD_SHIFT)
                d_iso_max -= 0.1;
            else if(mods & GLFW_MOD_CONTROL)
                d_n_iso = 1 > d_n_iso - 1 ? 1 : d_n_iso - 1;
            else
                d_iso_min -= 0.1;
        break;

        case GLFW_KEY_PERIOD:
            if (mods & GLFW_MOD_SHIFT)
                d_iso_max += 0.1;
            else if(mods & GLFW_MOD_CONTROL)
                ++d_n_iso;
            else
                d_iso_min += 0.1;
        break;
    }
}