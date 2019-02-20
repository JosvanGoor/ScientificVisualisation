#include "window.ih"

void Window::repaint(Simulation const &sim)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch(d_drawmode)
    {
        case DrawMode::SMOKE:
            paint_smoke(sim);
        break;

        case DrawMode::VECTORS:
            paint_vectors(sim);
        break;

        default:
            throw "Wtf this is impossible..."s;
    }

    glFlush();
    swap_buffers();
}