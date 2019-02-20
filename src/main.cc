#include "main.ih"

int main()
try
{
    if (!glfwInit())
    {
        cout << "error initializing glfw\n";
        return 2;
    }

    Window window;
    window.make_current();

    Simulation simulation;

    while (!window.should_close())
    {   
        simulation.simulation_step();
        window.repaint(simulation);

        glfwPollEvents();
    }

    glfwTerminate();
}
catch(string const &message)
{
    cout << "Caught error:\n";
    cout << "    " << message << "\n";

    glfwTerminate();

    return 1;
}