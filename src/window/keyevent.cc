#include "window.ih"

#include <iostream>

void Window::key_event(int key, int scancode, int action, int mods)
{
    cout << "key pressed: " << key << "\n";
}