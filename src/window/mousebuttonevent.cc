#include "window.ih"

#include <iostream>

void Window::mouse_button_event(int button, int action, int mods)
{
    cout << "mouse button event: " << button << "\n";
}