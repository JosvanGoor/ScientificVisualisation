#include "window.ih"

Window::Window(size_t width, size_t height)
:   d_min(0),
    d_max(1),
    d_width(width),
    d_height(height),
    d_mouse_lastx(0),
    d_mouse_lasty(0),
    d_mouse_dragging(false),
    d_vec_scale(1000),
    d_drawmode(DrawMode::NONE),
    d_colormapping(ColorMapping::BANDS),
    d_colormode(ColorMode::DENSITY),
    d_scalingmode(ScalingMode::STATIC),
    d_simulation(300),
    d_rendermodel()
{
    d_window = glfwCreateWindow
    (
        d_width,
        d_height,
        "Computer Visualisation",
        nullptr,
        nullptr
    );

    glfwSetWindowUserPointer(d_window, this);
    set_input_callbacks();
    
    if (!d_window)
        throw "Failed to create glfw window\n"s;
}