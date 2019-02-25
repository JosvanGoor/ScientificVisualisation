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

    window.set_drawmode(DrawMode::SMOKE);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    size_t iterations = 0;
    chrono::time_point t1 = chrono::high_resolution_clock::now();
    double simulation_time = 0.0;
    double graphics_time = 0.0;

    #pragma omp parallel
    {
        if (omp_get_thread_num() == 0)
            cout << "Running on " << omp_get_num_threads() << "threads\n";

        while (!window.should_close())
        {
            if (omp_get_thread_num() == 0)
            {
                ++iterations;
                t1 = chrono::high_resolution_clock::now();
            }
            window.simulation().simulation_step();
            
            #pragma omp barrier
            if (omp_get_thread_num() == 0)
            {
                simulation_time += chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count();
                chrono::time_point t1 = chrono::high_resolution_clock::now();
                window.repaint();
                graphics_time += chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count();
                
                if (iterations == 1000)
                {
                    cout.precision(3);
                    cout << "avg sim time over last 1000 iterations: " << simulation_time << "ms.\n";
                    cout << "avg gfx time over last 1000 iterations: " << graphics_time << "ms.\n";
                    simulation_time = 0;
                    graphics_time = 0;
                    iterations = 0;
                }

                glfwPollEvents();
            }
            
            //else the program wont end.
            #pragma omp barrier
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