#include "window.ih"

Window::Window(size_t width, size_t height)
:   d_width(width),
    d_height(height),
    d_mouse_lastx(0),
    d_mouse_lasty(0),
    d_mouse_dragging(false),
    d_vec_scale(1000),
    d_color_direction(false),
    d_drawmode(DrawMode::VECTORS),
    d_colormapping(ColorMapping::BLACKWHITE),
    d_rendermodel(nullptr),
    d_simulation(200)
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