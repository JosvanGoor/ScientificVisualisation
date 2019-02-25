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

    window.set_rendermodel(new SmokeRenderModel(200));
    glClearColor(0.0, 0.0, 0.0, 0.0);

    #pragma omp parallel
    {
        if (omp_get_thread_num() == 0)
            cout << "Running on " << omp_get_num_threads() << "threads\n";

        while (!window.should_close())
        {
            window.simulation().simulation_step();
            
            #pragma omp barrier
            if (omp_get_thread_num() == 0)
            {
                chrono::time_point t1 = chrono::high_resolution_clock::now();
                window.repaint();
                chrono::duration<double> elapsed = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1);
                cout << "gfx took " << elapsed.count() << "seconds\n\n";
                glfwPollEvents();
            }
        }
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