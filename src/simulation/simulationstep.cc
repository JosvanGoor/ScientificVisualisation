#include "simulation.ih"

#include <iostream>

void Simulation::simulation_step()
{
    if(!d_running)
        return;

    set_forces();
    solve();
    diffuse_matter();
}
