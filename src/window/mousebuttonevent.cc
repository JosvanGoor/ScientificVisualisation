#include "window.ih"

#include <iostream>

void Window::mouse_button_event(int button, int action, int mods)
{
    if (button != GLFW_MOUSE_BUTTON_1)
        return;

    if (action == GLFW_PRESS)
        d_mouse_dragging = true;
    else
        d_mouse_dragging = false;
}