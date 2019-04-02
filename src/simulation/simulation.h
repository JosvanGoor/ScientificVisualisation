#ifndef __SIMULATION_H_
#define __SIMULATION_H_

#include <string>
#include <vector>
#include <deque>

#include <fftw3.h>

template <int Size = 600>
class Simulation
{
    double d_timestep;
    double d_viscosity;
    bool d_running;
    size_t d_vfield_size;

    double* d_vfield_x;
    double* d_vfield_y;
    double* d_vfield0_x; //vorige step
    double* d_vfield0_y;

    std::deque<double*> d_history_x;
    std::deque<double*> d_history_y;
    
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
        size_t vfield_size() const;
        double timestep() const;
        double *vfield_x();
        double *vfield_y();
        std::deque<double *> &history_x();
        std::deque<double *> &history_y();
        std::vector<double> &rho();
        std::vector<double> &force_x();
        std::vector<double> &force_y();

    private:
        Simulation(Simulation const &copy) = delete;
        Simulation &operator=(Simulation const &copy) = delete;

        void set_forces();
        void solve();
        void diffuse_matter();
        void update_history();
};

template <int Size>
double Simulation<Size>::timestep() const
{
    return d_timestep;
}

template <int Size>
constexpr int Simulation<Size>::gridsize() const
{
    return Size;
}

template <int Size>
inline size_t Simulation<Size>::vfield_size() const
{
    return d_vfield_size;
}

template <int Size>
inline std::vector<double> &Simulation<Size>::rho()
{
    return d_rho;
}

template <int Size>
inline double *Simulation<Size>::vfield_x()
{
    return d_vfield_x;
}

template <int Size>
inline double *Simulation<Size>::vfield_y()
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

template <int Size>
inline std::deque<double*> &Simulation<Size>::history_y()
{
    return d_history_y;
}

template <int Size>
inline std::deque<double*> &Simulation<Size>::history_x()
{
    return d_history_x;
}

#include "diffusematter.f"
#include "setforces.f"
#include "simulation0.f"
#include "simulation1.f"
#include "simulationstep.f"
#include "solve.f"
#include "updatehistory.f"

#endif