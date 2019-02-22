#include "main.ih"

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int main()
try
{
    glfwSetErrorCallback(error_callback);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window window;
    window.make_current();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw "Failed to initialize GLAD"s;

    window.set_rendermodel(new LineRenderModel());
    glClearColor(0.0, 0.0, 0.0, 0.0);

    while (!window.should_close())
    {
        window.simulation().simulation_step();
        window.repaint();
        
        glfwPollEvents();
    }

    glfwTerminate();
}
catch(string const &error)
{
    cerr << "caught error:\n";
    cerr << "    " << error << "\n";

    glfwTerminate();

    return 1;
}