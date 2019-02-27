#include "window.ih"

#include <iostream>

void Window::repaint()
{
    if (!d_rendermodel)
    {
        cerr << "No current rendermodel! skipping draw.\n";
        return;
    }

    d_rendermodel->set_colormapping(static_cast<int>(d_colormapping));

    switch(d_drawmode)
    {
        case DrawMode::SMOKE:
            paint_smoke();
        break;

        case DrawMode::VECTORS:
            paint_vectors();
        break;

        case DrawMode::NONE:
            return;

        default:
            throw "Wtf this is impossible..."s;
    }
}