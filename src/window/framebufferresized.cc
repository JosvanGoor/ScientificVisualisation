#include "window.ih"

#include <iostream>

void Window::framebuffer_resized(int width, int height)
{
    cout << "framebuffer resized: " << width << " x " << height << "\n";

    d_width = width;
    d_height = height;

    glViewport(0, 0, width, height);
    
    if (d_drawmode == DrawMode::SMOKE || d_drawmode == DrawMode::SMOKE3D)
        initialize_smoke_render();
    
    if (d_rendermodel)
        d_rendermodel->framebuffer_size(width, height);

    d_arrows.set_framebuffer_size(width, height);
    d_glyphs.set_framebuffer_size(width, height);
    d_smoke3d.set_framebuffer_size(width, height, d_simulation.gridsize());
    d_streamtubes.set_framebuffer_size(width, height);
    d_helpfont.set_size(width, height);

}