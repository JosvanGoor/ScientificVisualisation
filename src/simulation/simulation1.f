#include "simulation.ih"

template <int Size>
Simulation<Size>::Simulation(double timestep, double viscosity)
:
    d_timestep(timestep),
    d_viscosity(viscosity),
    d_running(true)
{
    size_t dim = Size * 2 * (Size / 2 + 1);
    d_vfield_x.resize(dim, 0.0);
    d_vfield0_x.resize(dim, 0.0);
    d_vfield_y.resize(dim, 0.0);
    d_vfield0_y.resize(dim, 0.0);

    dim = Size * Size;
    d_force_x.resize(dim, 0.0);
    d_force_y.resize(dim, 0.0);
    d_rho.resize(dim, 0.0);
    d_rho0.resize(dim, 0.0);

    d_plan_ctor_1 = rfftw2d_create_plan(Size, Size,
        FFTW_COMPLEX_TO_REAL, FFTW_IN_PLACE);
    d_plan_ctor_2 = rfftw2d_create_plan(Size, Size,
        FFTW_COMPLEX_TO_REAL, FFTW_IN_PLACE);
    d_plan_rtoc_1 = rfftw2d_create_plan(Size, Size,
        FFTW_REAL_TO_COMPLEX, FFTW_IN_PLACE);
    d_plan_rtoc_2 = rfftw2d_create_plan(Size, Size,
        FFTW_REAL_TO_COMPLEX, FFTW_IN_PLACE);
}