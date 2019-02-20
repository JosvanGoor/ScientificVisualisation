#include "window.ih"

void Window::set_input_callbacks()
{
    glfwSetKeyCallback(d_window,
        [](GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            reinterpret_cast<Window *>(glfwGetWindowUserPointer(window))
                ->key_event(key, scancode, action, mods);
        });
    
    glfwSetMouseButtonCallback(d_window,
        [](GLFWwindow *window, int key, int action, int mods)
        {
            reinterpret_cast<Window *>(glfwGetWindowUserPointer(window))
                ->mouse_button_event(key, action, mods);
        });

    glfwSetCursorPosCallback(d_window,
        [](GLFWwindow *window, double xpos, double ypos)
        {
            reinterpret_cast<Window *>(glfwGetWindowUserPointer(window))
                ->mouse_moved(xpos, ypos);
        });

    glfwSetWindowSizeCallback(d_window,
        [](GLFWwindow *window, int width, int height)
        {
            reinterpret_cast<Window *>(glfwGetWindowUserPointer(window))
                ->window_resized(width, height);
        });
}