#include "main.ih"

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  


float vertices[] = 
{
    -0.5f, -0.5f,
    0.0f, 0.0f,

    1.0f, 0.0f,
    0.0f, 0.0f
};

float colors[] = 
{
    1.0, 0.0, 0.0,
    1.0, 1.0, 1.0,

    0.0, 1.0, 0.0,
    1.0, 1.0, 1.0
};


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

    /*
        DRAWING A TRIANGLE
     */

    GLuint vshader = compile_shader(read_file("shaders/vertex.glsl"), GL_VERTEX_SHADER);
    GLuint fshader = compile_shader(read_file("shaders/fragment.glsl"), GL_FRAGMENT_SHADER);
    GLuint program = link_program(vshader, fshader);

    glUseProgram(program);
    //del shaders

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    GLuint cbo;
    glGenBuffers(1, &cbo);
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /*
        END PREPARATION
    */

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_LINES, 0, 4);

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