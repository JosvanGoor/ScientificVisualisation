#include "window.ih"

#include <iostream>

void Window::repaint()
{
    if (!d_rendermodel)
        cerr << "No current rendermodel! skipping draw.\n";

    switch(d_drawmode)
    {
        case DrawMode::SMOKE:
            paint_smoke();
        break;

        case DrawMode::VECTORS:
            paint_vectors();
        break;

        default:
            throw "Wtf this is impossible..."s;
    }

    swap_buffers();
}