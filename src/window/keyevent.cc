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
                    (static_cast<int>(d_colormapping) + 1) % 3
                )
            );
            cout << "Set: " << colormapping_string(d_colormapping) << "          \r" << flush;
        break;

        case GLFW_KEY_R:
            set_drawmode
            (
                static_cast<DrawMode>
                (
                    (static_cast<int>(d_drawmode) + 1) % 2
                )
            );
            cout << "Set: " << drawmode_string(d_drawmode) << "          \r" << flush;
        break;
    }
}