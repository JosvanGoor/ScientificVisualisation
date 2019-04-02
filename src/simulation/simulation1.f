#include "simulation.ih"

template <int Size>
Simulation<Size>::Simulation(double timestep, double viscosity)
:
    d_timestep(timestep),
    d_viscosity(viscosity),
    d_running(true),
    d_vfield_size(Size * 2 * (Size / 2 + 1)),
    d_history_x(max(Size, 200)),
    d_history_y(max(Size, 200))
{
    
    for (size_t idx = 0; idx != d_history_x.size(); ++idx)
    {
        d_history_x[idx] = fftw_alloc_real(d_vfield_size); 
        d_history_y[idx] = fftw_alloc_real(d_vfield_size); 
    }

    d_vfield_x = fftw_alloc_real(d_vfield_size);
    d_vfield_y = fftw_alloc_real(d_vfield_size);
    d_vfield0_x = fftw_alloc_real(d_vfield_size);
    d_vfield0_y = fftw_alloc_real(d_vfield_size);

    fftw_import_wisdom_from_filename("wisdom");

    d_plan_ctor_x = fftw_plan_dft_c2r_2d(Size, Size,
        reinterpret_cast<fftw_complex *>(d_vfield0_x), 
            d_vfield0_x,
            FFTW_PATIENT);
    d_plan_ctor_y = fftw_plan_dft_c2r_2d(Size, Size,
        reinterpret_cast<fftw_complex *>(d_vfield0_y), 
             d_vfield0_y,
            FFTW_PATIENT);
    d_plan_rtoc_x = fftw_plan_dft_r2c_2d(Size, Size,
            d_vfield0_x,
             reinterpret_cast<fftw_complex *>(d_vfield0_x),
            FFTW_PATIENT);
    d_plan_rtoc_y = fftw_plan_dft_r2c_2d(Size, Size,
            d_vfield0_y, 
             reinterpret_cast<fftw_complex *>(d_vfield0_y),
            FFTW_PATIENT);

    fftw_export_wisdom_to_filename("wisdom");

    // required else we get NAN contents for small gridsizes (<200).
    for (size_t idx = 0; idx < d_vfield_size; ++idx)
    {
        d_vfield_x[idx] = 0.0;
        d_vfield0_x[idx] = 0.0;
        d_vfield0_y[idx] = 0.0;
        d_vfield_y[idx] = 0.0;
    }

    size_t dim = Size * Size;
    d_force_x.resize(dim, 0.0);
    d_force_y.resize(dim, 0.0);
    d_rho.resize(dim, 0.0);
    d_rho0.resize(dim, 0.0);
}