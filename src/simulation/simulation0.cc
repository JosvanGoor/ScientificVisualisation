#include "simulation.ih"

Simulation::~Simulation()
{
    rfftwnd_destroy_plan(d_plan_rtoc);
    rfftwnd_destroy_plan(d_plan_ctor);
}