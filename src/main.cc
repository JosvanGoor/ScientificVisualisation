#include "main.ih"

void error_callback(int error, char const *description)
{
    cerr << "glfw error#" << error << ": " << description << "\n";
}

void check_opengl_errors()
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        cerr << "OpenGL error: " << err << "\n";
    }
}

int main()
try
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        cout << "error initializing glfw\n";
        return 2;
    }

    Window window;
    
    window.mouse_button_event(GLFW_MOUSE_BUTTON_1, GLFW_PRESS, 0);
    window.mouse_moved(10, 10);
    window.mouse_moved(20, 20);
    window.mouse_button_event(GLFW_MOUSE_BUTTON_1, GLFW_RELEASE, 0);

    window.make_current();

    while (!window.should_close())
    {   
        glfwPollEvents();
        window.simulation().simulation_step();
        window.repaint();

        check_opengl_errors();
    }

    glfwTerminate();
    cout << "Following glfw error#65537 is not a problem.\n";
}
catch(string const &message)
{
    cout << "Caught error:\n";
    cout << "    " << message << "\n";

    glfwTerminate();

    return 1;
}