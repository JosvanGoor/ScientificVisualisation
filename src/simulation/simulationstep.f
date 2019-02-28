#include "simulation.ih"
#include <iostream>
#include <omp.h>

template <int Size>
void Simulation<Size>::simulation_step()
{
    if(!d_running)
        return;

    set_forces();
    solve();
    diffuse_matter();
}