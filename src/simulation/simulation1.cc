#include "simulation.ih"

Simulation::Simulation(int gridsize, double timestep, double viscosity)
:
    d_gridsize(gridsize),
    d_timestep(timestep),
    d_viscosity(viscosity),
    d_running(true)
{
    size_t dim = d_gridsize * 2 * (d_gridsize / 2 + 1);
    d_vfield_x.resize(dim, 0.0);
    d_vfield0_x.resize(dim, 0.0);
    d_vfield_y.resize(dim, 0.0);
    d_vfield0_y.resize(dim, 0.0);

    dim = d_gridsize * d_gridsize;
    d_force_x.resize(dim, 0.0);
    d_force_y.resize(dim, 0.0);
    d_rho.resize(dim, 0.0);
    d_rho0.resize(dim, 0.0);

    d_plan_ctor = rfftw2d_create_plan(d_gridsize, d_gridsize,
        FFTW_COMPLEX_TO_REAL, FFTW_IN_PLACE);
    d_plan_rtoc = rfftw2d_create_plan(d_gridsize, d_gridsize,
        FFTW_REAL_TO_COMPLEX, FFTW_IN_PLACE);
}