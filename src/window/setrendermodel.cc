#include "window.ih"

void Window::set_rendermodel(RenderModel *model)
{
    if (d_rendermodel)
        delete d_rendermodel;

    d_rendermodel = model;
    d_rendermodel->framebuffer_size(d_width, d_height);
}