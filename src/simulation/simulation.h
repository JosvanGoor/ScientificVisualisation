#ifndef __SIMULATION_H_
#define __SIMULATION_H_

#include <string>
#include <vector>

#include <fftw3.h>

template <int Size = 600>
class Simulation
{
    double d_timestep;
    double d_viscosity;
    bool d_running;

    std::vector<double> d_vfield_x;
    std::vector<double> d_vfield_y;
    std::vector<double> d_vfield0_x; //vorige step
    std::vector<double> d_vfield0_y;
    
    std::vector<double> d_force_x;
    std::vector<double> d_force_y;
    std::vector<double> d_rho;
    std::vector<double> d_rho0; // vorige step

    // geen idee wat dit doet.
    fftw_plan d_plan_ctor_x;
    fftw_plan d_plan_ctor_y;
    fftw_plan d_plan_rtoc_x;
    fftw_plan d_plan_rtoc_y;

    public:
        Simulation(double timestep = 0.4, double viscosity = 0.001);
        ~Simulation();

        void simulation_step();

        //getters
        constexpr int gridsize() const;
        std::vector<double> &vfield_x();
        std::vector<double> &vfield_y();
        std::vector<double> &rho();
        std::vector<double> &force_x();
        std::vector<double> &force_y();

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
inline std::vector<double> &Simulation<Size>::rho()
{
    return d_rho;
}

template <int Size>
inline std::vector<double> &Simulation<Size>::vfield_x()
{
    return d_vfield_x;
}

template <int Size>
inline std::vector<double> &Simulation<Size>::vfield_y()
{
    return d_vfield_y;
}

template <int Size>
inline std::vector<double> &Simulation<Size>::force_x()
{
    return d_force_x;
}

template <int Size>
inline std::vector<double> &Simulation<Size>::force_y()
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