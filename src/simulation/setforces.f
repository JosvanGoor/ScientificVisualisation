#include "simulation.ih"

template <int Size>
void Simulation<Size>::set_forces()
{
    #pragma omp for
    for (int idx = 0; idx < Size * Size; ++idx)
    {
        d_rho0[idx] = 0.995 * d_rho[idx];
        d_force_x[idx] *= 0.85;
        d_force_y[idx] *= 0.85;
        d_vfield0_x[idx] = d_force_x[idx];
        d_vfield0_y[idx] = d_force_y[idx];
    }
}