#include "simulation.ih"

template <int Size>
Simulation<Size>::Simulation(double timestep, double viscosity)
:
    d_timestep(timestep),
    d_viscosity(viscosity),
    d_running(true),
    d_vfield_x(Size * 2 * (Size / 2 + 1)),
    d_vfield_y(Size * 2 * (Size / 2 + 1)),
    d_vfield0_x(Size * 2 * (Size / 2 + 1)),
    d_vfield0_y(Size * 2 * (Size / 2 + 1))
{

    d_plan_ctor_x = fftw_plan_dft_c2r_2d(Size, Size,
        reinterpret_cast<fftw_complex *>(d_vfield0_x.data()), 
             (double *) d_vfield0_x.data(),
            FFTW_MEASURE);
    d_plan_ctor_y = fftw_plan_dft_c2r_2d(Size, Size,
        reinterpret_cast<fftw_complex *>(d_vfield0_y.data()), 
             (double *) d_vfield0_y.data(),
            FFTW_MEASURE);
    d_plan_rtoc_x = fftw_plan_dft_r2c_2d(Size, Size,
        (double *) d_vfield0_x.data(), 
             reinterpret_cast<fftw_complex *>(d_vfield0_x.data()),
            FFTW_MEASURE);
    d_plan_rtoc_y = fftw_plan_dft_r2c_2d(Size, Size,
        (double *) d_vfield0_y.data(), 
             reinterpret_cast<fftw_complex *>(d_vfield0_y.data()),
            FFTW_MEASURE);

    size_t dim = Size * Size;
    d_force_x.resize(dim, 0.0);
    d_force_y.resize(dim, 0.0);
    d_rho.resize(dim, 0.0);
    d_rho0.resize(dim, 0.0);
}