#include "main.ih"
#include <fftw3.h>


void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int main()
try
{
    
    omp_set_nested(1);
    glfwSetErrorCallback(error_callback);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window window{1350, 850};
    
    window.make_current();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw "Failed to initialize GLAD"s;

    window.init_glyps();

    window.set_drawmode(DrawMode::SMOKE);
    
    glClearColor(0.0, 0.0, 0.0, 0.0);

    RenderFont font{"fonts/comic.ttf", 16};
    RenderFont::String status = font.create_string("initial");

    size_t iterations = 0;
    chrono::time_point t1 = chrono::high_resolution_clock::now();
    double simulation_time = 0.0;
    double graphics_time = 0.0;

    #pragma omp parallel
    {
        if (omp_get_thread_num() == 0)
        {
            cout << "Running on " << omp_get_num_threads() << "threads\n";
            window.print_shortcuts();
        }

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
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                simulation_time += chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count();
                chrono::time_point t1 = chrono::high_resolution_clock::now();

                window.repaint();
                
                auto &sim = window.simulation();

                font.set_size(window.width(), window.height());
                font.update_string(status, window.print_settings());
                font.render_string_outlined(status, glm::vec2{10.0f, 5.0f});

                graphics_time += chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count();
                
                if (iterations == 100)
                {
                    cout.precision(3);
                    cout << "avg sim time over last 100 iterations: " << simulation_time*10 << "ms.\n";
                    cout << "avg gfx time over last 100 iterations: " << graphics_time*10 << "ms.\n";
                    window.print_shortcuts();
                    simulation_time = 0;
                    graphics_time = 0;
                    iterations = 0;
                }
                window.swap_buffers();
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