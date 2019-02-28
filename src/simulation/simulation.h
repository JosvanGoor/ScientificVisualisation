#ifndef __SIMULATION_H_
#define __SIMULATION_H_

#include <string>
#include <vector>

#include <rfftw.h>

template <int Size = 300>
class Simulation
{
    double d_timestep;
    double d_viscosity;
    bool d_running;

    std::vector<fftw_real> d_vfield_x;
    std::vector<fftw_real> d_vfield_y;
    std::vector<fftw_real> d_vfield0_x; //vorige step
    std::vector<fftw_real> d_vfield0_y;
    
    std::vector<fftw_real> d_force_x;
    std::vector<fftw_real> d_force_y;
    std::vector<fftw_real> d_rho;
    std::vector<fftw_real> d_rho0; // vorige step

    // geen idee wat dit doet.
    rfftwnd_plan d_plan_rtoc_1;
    rfftwnd_plan d_plan_rtoc_2;
    rfftwnd_plan d_plan_ctor_1;
    rfftwnd_plan d_plan_ctor_2;

    public:
        Simulation(double timestep = 0.4, double viscosity = 0.001);
        ~Simulation();

        void simulation_step();

        //getters
        constexpr int gridsize() const;
        std::vector<fftw_real> const &vfield_x() const;
        std::vector<fftw_real> const &vfield_y() const;
        std::vector<fftw_real> &rho();
        std::vector<fftw_real> &force_x();
        std::vector<fftw_real> &force_y();

    private:
        Simulation(Simulation const &copy) = delete;
        Simulation &operator=(Simulation const &copy) = delete;

        void set_forces();
        void solve();
        void diffuse_matter();

};

template <int Size>
constexpr int Simulation<Size>::gridsize() const
{
    return Size;
}

template <int Size>
inline std::vector<fftw_real> &Simulation<Size>::rho()
{
    return d_rho;
}

template <int Size>
inline std::vector<fftw_real> const &Simulation<Size>::vfield_x() const
{
    return d_vfield_x;
}

template <int Size>
inline std::vector<fftw_real> const &Simulation<Size>::vfield_y() const
{
    return d_vfield_y;
}

template <int Size>
inline std::vector<fftw_real> &Simulation<Size>::force_x()
{
    return d_force_x;
}

template <int Size>
inline std::vector<fftw_real> &Simulation<Size>::force_y()
{
    return d_force_y;
}

#include "diffusematter.f"
#include "setforces.f"
#include "simulation0.f"
#include "simulation1.f"
#include "simulationstep.f"
#include "solve.f"

#endif