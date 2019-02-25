#include "simulation.ih"

#include <iostream>

void Simulation::simulation_step()
{
    if(!d_running)
        return;

    chrono::time_point t1 = chrono::high_resolution_clock::now();

    set_forces();
    solve();
    diffuse_matter();

    chrono::duration<double> elapsed = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1);
    cout << "sim took " << elapsed.count() << "seconds\n";
}
