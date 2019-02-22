#include "simulation.ih"

#include <iostream>

void Simulation::set_forces()
{
    for (int idx = 0; idx < d_gridsize * d_gridsize; ++idx)
    {
        d_rho0[idx] = 0.995 * d_rho[idx];
        d_force_x[idx] *= 0.85;
        d_force_y[idx] *= 0.85;
        d_vfield0_x[idx] = d_force_x[idx];
        d_vfield0_y[idx] = d_force_y[idx];
    }
}