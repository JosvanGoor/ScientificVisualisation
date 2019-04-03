#include "window.ih"

Window::Window(size_t width, size_t height)
:   d_iso_min(0),
    d_iso_max(1),
    d_n_iso(4),
    d_min(0),
    d_max(1),
    d_width(width),
    d_height(height),
    d_mouse_lastx(0),
    d_mouse_lasty(0),
    d_mouse_dragging(false),
    d_vec_scale(1000),
    d_drawmode(DrawMode::NONE),
    d_colormapping(ColorMapping::DUTCH),
    d_isoline_mapping(ColorMapping::BLACK),
    d_colormode(ColorMode::DENSITY),
    d_heightmode(ColorMode::DENSITY),
    d_scalar_mode(ColorMode::DENSITY),
    d_scalingmode(ScalingMode::STATIC),
    d_glyphmode(GlyphMode::NONE),
    d_divmode(DivMode::OFF),
    d_isomode(IsolineMode::OFF),
    d_simulation(),
    d_rendermodel(),
    d_help(false),
    d_arrows()
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