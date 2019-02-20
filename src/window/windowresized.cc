#include "window.ih"

#include <iostream>

void Window::window_resized(int width, int height)
{
    cout << "window resized: " << width << " x " << height << "\n";

    glViewport(.0f, .0f, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(.0, width, 0.0, height);

    d_width = width;
    d_height = height;
}