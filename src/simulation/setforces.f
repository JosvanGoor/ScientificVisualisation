#include "simulation.ih"
#include <algorithm>
#include <iostream>


template <int Size>
void Simulation<Size>::set_forces()
{
    #pragma omp sections
    {
        {std::transform(d_rho.begin(),d_rho.end(),
                        d_rho0.begin(), [](float lhs){
                            return lhs * 0.995;
                        });}
        #pragma omp section
        {std::transform(d_force_x.begin(),d_force_x.end(),
                        d_force_x.begin(), [](float lhs){
                            return lhs * 0.85;
                        });}
        #pragma omp section
        {std::transform(d_force_y.begin(),d_force_y.end(),
                        d_force_y.begin(), [](float lhs){
                            return lhs * 0.85;
                        });}
    }

    #pragma omp for simd
    for(size_t i = 0; i < Size*Size; ++i)
    {
        d_vfield0_x[i] = d_force_x[i];
        d_vfield0_y[i] = d_force_y[i];
    }
}
