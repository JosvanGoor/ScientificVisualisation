#include "window.ih"

#include <iostream>

void Window::framebuffer_resized(int width, int height)
{
    cout << "framebuffer resized: " << width << " x " << height << "\n";

    glViewport(0, 0, width, height);
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // gluOrtho2D(.0, width, 0.0, height);

    // d_width = width;
    // d_height = height;
}