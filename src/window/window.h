#ifndef __INCLUDED_WINDOW_H_
#define __INCLUDED_WINDOW_H_

#include <array>
#include <memory>

#include "../linerendermodel/linerendermodel.h"
#include "../smokerendermodel/smokerendermodel.h"
#include "../simulation/simulation.h"
#include <GLFW/glfw3.h>

enum class DrawMode
{
    SMOKE,
    VECTORS,
    TEST
};

enum class ColorMapping
{
    BLACKWHITE,
    RAINBOW,
    BANDS
};

typedef std::array<float, 3> Color;

class Window
{
    size_t d_width;
    size_t d_height;
    GLFWwindow *d_window;

    double d_mouse_lastx;
    double d_mouse_lasty;
    bool d_mouse_dragging;

    float d_vec_scale;
    bool d_color_direction;
    DrawMode d_drawmode;
    ColorMapping d_colormapping;
    
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

        // callbacks
        void key_event(int key, int scancode, int action, int mods);
        void mouse_button_event(int button, int action, int mods);
        void mouse_moved(double xpos, double ypos);
        void framebuffer_resized(int width, int height);

    private:
        Window(Window const &copy) = delete;
        Window &operator=(Window const &copy) = delete;

        void set_input_callbacks();

        Color colormap(float col);
        Color direction_to_color(float x, float y);

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

#endif