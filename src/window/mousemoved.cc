#include "window.ih"

#include <iostream>

void Window::mouse_moved(double xpos, double ypos)
{
    cout << "mouse pos: " << xpos << ", " << ypos << "\n";
}