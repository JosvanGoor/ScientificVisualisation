#include "window.ih"

#include <iostream>

void Window::framebuffer_resized(int width, int height)
{
    cout << "framebuffer resized: " << width << " x " << height << "\n";

    d_width = width;
    d_height = height;

    glViewport(0, 0, width, height);
    if (d_rendermodel)
        d_rendermodel->framebuffer_size(width, height);
}