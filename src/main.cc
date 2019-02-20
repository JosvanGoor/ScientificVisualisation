#include "main.ih"

void error_callback(int error, char const *description)
{
    cerr << "glfw error#" << error << ": " << description << "\n";
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
    window.make_current();

    while (!window.should_close())
    {   
        glfwPollEvents();
        window.simulation().simulation_step();
        window.repaint();
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