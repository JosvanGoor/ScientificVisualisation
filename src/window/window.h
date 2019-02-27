#ifndef __INCLUDED_WINDOW_H_
#define __INCLUDED_WINDOW_H_

#include <array>
#include <memory>
#include <iostream>

#include "../linerendermodel/linerendermodel.h"
#include "../smokerendermodel/smokerendermodel.h"
#include "../simulation/simulation.h"
#include <GLFW/glfw3.h>

enum class DrawMode
{
    SMOKE,
    VECTORS,
    NONE
};
std::string drawmode_string(DrawMode mode);

enum class ColorMapping
{
    BLACKWHITE,
    RAINBOW,
    BANDS
};
std::string colormapping_string(ColorMapping mapping);

enum class ColorMode
{
    DENSITY,
    FORCE,
    VELOCITY
};
std::string colormode_string(ColorMode mode);


enum class ScalingMode
{
    STATIC,
    DYNAMIC
};
std::string scalingmode_string(ScalingMode mode);
typedef std::array<float, 3> Color;

class Window
{
    float d_min, d_max;
    size_t d_width;
    size_t d_height;
    GLFWwindow *d_window;

    double d_mouse_lastx;
    double d_mouse_lasty;
    bool d_mouse_dragging;

    float d_vec_scale;
    DrawMode d_drawmode;
    ColorMapping d_colormapping;
    ColorMode d_colormode;
    ScalingMode d_scalingmode;
    
    Simulation d_simulation;
    std::unique_ptr<RenderModel> d_rendermodel;

    public:
        Window(size_t width = 500, size_t height = 500);
        ~Window();

        bool should_close();
        void swap_buffers();
        void make_current();
        Simulation &simulation();

        void repaint();
        void set_drawmode(DrawMode mode);
        void set_colormapping(ColorMapping mapping);
        void set_colormode(ColorMode mode);
        void set_scalingmode(ScalingMode mode);
        
        void print_shortcuts() const;
        void print_settings() const;

        // callbacks
        void key_event(int key, int scancode, int action, int mods);
        void mouse_button_event(int button, int action, int mods);
        void mouse_moved(double xpos, double ypos);
        void framebuffer_resized(int width, int height);

    private:
        Window(Window const &copy) = delete;
        Window &operator=(Window const &copy) = delete;

        void set_input_callbacks();

        void initialize_smoke_render();

        void paint_smoke();
        void paint_vectors();
};

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

inline Simulation &Window::simulation()
{
    return d_simulation;
}

inline void Window::set_colormapping(ColorMapping mapping)
{
    d_colormapping = mapping;
}

inline void Window::set_colormode(ColorMode mode)
{
    d_colormode = mode;
}

inline void Window::set_scalingmode(ScalingMode mode)
{
    d_scalingmode = mode;
}

inline void Window::print_settings() const
{
    std::cout << "Settings: "
              << "{" << drawmode_string(d_drawmode) << "}:"
              << "{" << scalingmode_string(d_scalingmode);
    if (d_scalingmode == ScalingMode::STATIC) 
        std::cout << ": between: [" << d_min << ", " << d_max << ']';
    std::cout << "}:"
              << " " << colormapping_string(d_colormapping) << " -> "
              << colormode_string(d_colormode) << "               \r" << std::flush;
}

#endif