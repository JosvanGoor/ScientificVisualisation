#include "simulation.ih"
#include <algorithm>
#include <iostream>


template <int Size>
void Simulation<Size>::set_forces()
{
    #pragma omp for
    for (size_t idx = 0; idx < d_rho0.size(); ++idx)
    {
        d_rho0[idx] = 0.995 * d_rho[idx];
        d_force_x[idx] = 0.85 * d_force_x[idx];
        d_force_y[idx] = 0.85 * d_force_y[idx];
    }

    // #pragma omp for simd
    // for(size_t i = 0; i < Size*Size; ++i)
    // {
    //     d_vfield0_x[i] = d_force_x[i];
    //     d_vfield0_y[i] = d_force_y[i];
    // }
}
