#include "window.ih"

void Window::set_drawmode(DrawMode mode)
{
    switch(mode)
    {
        case DrawMode::SMOKE:
            initialize_smoke_render();
        break;

        case DrawMode::VECTORS:
            d_rendermodel = std::make_unique<LineRenderModel>();
        break;

        default:
            throw "wtf this is impossible."s;
    }

    d_rendermodel->framebuffer_size(d_width, d_height);
    d_drawmode = mode;
}