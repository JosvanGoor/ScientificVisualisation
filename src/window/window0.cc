#include "window.ih"

Window::~Window()
{
    glfwDestroyWindow(d_window);
}