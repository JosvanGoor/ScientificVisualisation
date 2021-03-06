#ifndef __INCLUDED_WINDOW_H_
#define __INCLUDED_WINDOW_H_

#include <array>
#include <memory>
#include <iostream>
#include <sstream>

#include "../enums/enums.h"
#include "../streamtuberendermodel/streamtuberendermodel.h"
#include "../isoline2drendermodel/isoline2drendermodel.h"
#include "../linerendermodel/linerendermodel.h"
#include "../smoke3drendermodel/smoke3drendermodel.h"
#include "../smokerendermodel/smokerendermodel.h"
#include "../simulation/simulation.h"
#include "../arrow3drendermodel/arrow3drendermodel.h"
#include "../glyph2drendermodel/glyph2drendermodel.h"
#include <GLFW/glfw3.h>

typedef Simulation<200> t_Simulation;

class Window
{
    double d_iso_min, d_iso_max;
    size_t d_n_iso;
    double v_min;
    double v_max;
    double dyn_min;
    double dyn_max;
    double d_min, d_max;
    size_t d_width;
    size_t d_height;
    GLFWwindow *d_window;

    double d_mouse_lastx;
    double d_mouse_lasty;
    float d_mouse_z;
    double d_mouse_zx;
    double d_mouse_zy;
    bool d_mouse_dragging;

    float d_vec_scale;
    DrawMode d_drawmode;
    ColorMapping d_colormapping;
    ColorMapping d_isoline_mapping;
    ColorMode d_colormode;
    ColorMode d_heightmode;
    ColorMode d_scalar_mode;
    ScalingMode d_scalingmode;
    GlyphMode d_glyphmode;
    DivMode d_divmode;
    IsolineMode d_isomode;
    
    t_Simulation d_simulation;
    std::unique_ptr<RenderModel> d_rendermodel;

    bool d_help;
    RenderFont d_helpfont;
    RenderFont::String d_helpstring;

    Smoke3dRenderModel d_smoke3d;
    Isoline2dRenderModel d_iso2d;
    Glyph2dRenderModel d_glyphs;
    Arrow3dRenderModel d_arrows;
    StreamtubeRenderModel d_streamtubes;

    vector<float> store;
    vector<float> lines;
    vector<float> stream_lines;
    vector<glm::vec3> d_streamline_anchors;

    public:
        Window(size_t width = 500, size_t height = 500);
        ~Window();

        size_t width() const;
        size_t height() const;

        bool should_close();
        void swap_buffers();
        void make_current();
        t_Simulation &simulation();

        void repaint();
        void set_drawmode(DrawMode mode);
        void set_colormapping(ColorMapping mapping);
        void set_isoline_colormapping(ColorMapping mapping);
        void set_colormode(ColorMode mode);
        void set_scalarmode(ColorMode mode);
        void set_heightmode(ColorMode mode);
        void set_scalingmode(ScalingMode mode);
        void set_glyphmode(GlyphMode mode);
        void set_divmode(DivMode mode);
        void set_isomode(IsolineMode mode);

        std::string print_shortcuts() const;
        std::string print_settings() const;

        // callbacks
        void key_event(int key, int scancode, int action, int mods);
        void mouse_button_event(int button, int action, int mods);
        void mouse_moved(double xpos, double ypos);
        void framebuffer_resized(int width, int height);

        void initialize();

    private:
        Window(Window const &copy) = delete;
        Window &operator=(Window const &copy) = delete;

        glm::vec3 unproject_mouse() const;

        void calcStore();
        void calc_lines(double iso);
        void calc_streamline(size_t x, size_t y, size_t z);

        void set_input_callbacks();
        void initialize_smoke_render();
        void paint_smoke();

        template <typename T>
        void divergence(T vecX, T vecY);
        void paint_vectors();
};

#include "divergence.f"

inline void Window::initialize()
{
    d_smoke3d.initialize();
    d_glyphs.initialize();
    d_arrows.initialize();
    d_iso2d.initialize();
    d_streamtubes.initialize();

    d_helpfont = RenderFont("fonts/comic.ttf", 24);
    d_helpstring = d_helpfont.create_string(print_shortcuts(), GL_STATIC_DRAW);

    framebuffer_resized(d_width, d_height);
}

inline size_t Window::width() const
{
    return d_width;
}

inline size_t Window::height() const
{
    return d_height;
}

inline bool Window::should_close()
{
    return glfwWindowShouldClose(d_window);
}

inline void Window::swap_buffers()
{
    glfwSwapBuffers(d_window);
}

inline void Window::make_current()
{
    glfwMakeContextCurrent(d_window);
}

inline t_Simulation &Window::simulation()
{
    return d_simulation;
}

inline void Window::set_colormapping(ColorMapping mapping)
{
    d_colormapping = mapping;
}

inline void Window::set_isoline_colormapping(ColorMapping mapping)
{
    d_isoline_mapping = mapping;
    d_iso2d.set_colormapping(mapping);
}

inline void Window::set_colormode(ColorMode mode)
{
    d_colormode = mode;
}

inline void Window::set_scalarmode(ColorMode mode)
{
    d_scalar_mode = mode;
}

inline void Window::set_heightmode(ColorMode mode)
{
    d_heightmode = mode;
}

inline void Window::set_scalingmode(ScalingMode mode)
{
    d_scalingmode = mode;
}

inline void Window::set_glyphmode(GlyphMode mode)
{
    d_glyphmode = mode;
}

inline void Window::set_divmode(DivMode mode)
{
    d_divmode = mode;
}

inline void Window::set_isomode(IsolineMode mode)
{
    d_isomode = mode;
}

inline std::string Window::print_settings() const
{
    std::stringstream ss;
    ss << "DrawMode: {" << drawmode_string(d_drawmode) << "}:";
    ss << "{" << scalingmode_string(d_scalingmode);
    
    if (d_scalingmode == ScalingMode::STATIC)
        ss << ": between [" << d_min << ", " << "d_max" << "]";
    ss << "} ";
    
    ss << colormapping_string(d_colormapping) << " -> ";
    ss << colormode_string(d_colormode) << "\n";

    ss << "Heightmap:";
    ss << " ColorMode scalar -> height: ";
    ss << colormode_string(d_heightmode) << "\n";

    ss << "Overlays: [ ";
    if (d_glyphmode != GlyphMode::NONE)
        ss << glyphmode_string(d_glyphmode) << " ";
    if (d_isomode != IsolineMode::OFF)
    {
        ss << isoline_string(d_isomode) << " (";
        ss << colormapping_string(d_isoline_mapping) << ") ";
    }
    ss << "]";

    return ss.str();
}

#endif
