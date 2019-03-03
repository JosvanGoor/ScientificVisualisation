#include "simulation.ih"

template <int Size>
Simulation<Size>::~Simulation()
{
    fftw_destroy_plan(d_plan_rtoc_x);
    fftw_destroy_plan(d_plan_rtoc_y);
    fftw_destroy_plan(d_plan_ctor_x);
    fftw_destroy_plan(d_plan_ctor_y);
    fftw_free(d_vfield0_x);
    fftw_free(d_vfield_x);
    fftw_free(d_vfield0_y);
    fftw_free(d_vfield_y);
}