#include "simulation.ih"

template <int Size>
Simulation<Size>::~Simulation()
{
    rfftwnd_destroy_plan(d_plan_rtoc);
    rfftwnd_destroy_plan(d_plan_ctor);
}