#ifndef __INCLUDED_WINDOW_H_
#define __INCLUDED_WINDOW_H_

#include <GLFW/glfw3.h>
#include "../simulation/simulation.h"

enum class DrawMode
{
    SMOKE,
    VECTORS
};

enum class ColorMapping
{
    BLACKWHITE,
    RAINBOW,
    BANDS
};

class Window
{
    size_t d_width;
    size_t d_height;

    float d_vec_scale;
    bool d_color_direction;
    DrawMode d_drawmode;
    ColorMapping d_colormapping;
    
    GLFWwindow *d_window;

    public:
        Window(size_t width = 500, size_t height = 500);
        ~Window();

        bool should_close();
        void swap_buffers();
        void make_current();

        void repaint(Simulation const &sim);

    private:
        Window(Window const &copy) = delete;
        Window &operator=(Window const &copy) = delete;

        void set_colormap(float col);
        void direction_to_color(float x, float y);

        void paint_smoke(Simulation const &sim);
        void paint_vectors(Simulation const &sim);

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

#endif