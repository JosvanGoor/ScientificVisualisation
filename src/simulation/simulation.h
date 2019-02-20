#ifndef __SIMULATION_H_
#define __SIMULATION_H_

#include <vector>

#include <rfftw.h>

class Simulation
{
    int d_gridsize;
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
    rfftwnd_plan d_plan_rtoc;
    rfftwnd_plan d_plan_ctor;

    public:
        Simulation(int gridsize = 50, double timestep = 0.4, double viscosity = 0.001);
        ~Simulation();

        void simulation_step();

        //getters
        int gridsize() const;
        std::vector<fftw_real> const &rho() const;
        std::vector<fftw_real> const &vfield_x() const;
        std::vector<fftw_real> const &vfield_y() const;

    private:
        Simulation(Simulation const &copy) = delete;
        Simulation &operator=(Simulation const &copy) = delete;

        void set_forces();
        void solve();
        void diffuse_matter();

};

inline int Simulation::gridsize() const
{
    return d_gridsize;
}

inline std::vector<fftw_real> const &Simulation::rho() const
{
    return d_rho;
}

inline std::vector<fftw_real> const &Simulation::vfield_x() const
{
    return d_vfield_x;
}

inline std::vector<fftw_real> const &Simulation::vfield_y() const
{
    return d_vfield_y;
}

#endif