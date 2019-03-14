#include "window.ih"

#include <iostream>

void Window::framebuffer_resized(int width, int height)
{
    cout << "framebuffer resized: " << width << " x " << height << "\n";

    d_width = width;
    d_height = height;

    glViewport(0, 0, width, height);
    
    // d_iso2d.set_size(width, height);

    if (d_drawmode == DrawMode::SMOKE)
        initialize_smoke_render();
    
    if (d_rendermodel)
        d_rendermodel->framebuffer_size(width, height);

}