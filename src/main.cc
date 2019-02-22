#include "main.ih"

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

int main()
try
{
    glfwSetErrorCallback(error_callback);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(500, 500, "jajajaja", nullptr, nullptr);
    if (!window)
        throw "Failed to create glfw window"s;
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw "Failed to initialize GLAD"s;

    glViewport(0, 0, 500, 500);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    LineRenderModel model;

    size_t frame = 0;
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2, 0.3, 0.3, 1.0);
        
        model.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
catch(string const &error)
{
    cerr << "caught error:\n";
    cerr << "    " << error << "\n";
    return 1;
}