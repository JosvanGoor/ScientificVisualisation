#include "simulation.ih"

template <int Size>
Simulation<Size>::~Simulation()
{
    rfftwnd_destroy_plan(d_plan_rtoc_1);
    rfftwnd_destroy_plan(d_plan_rtoc_2);
    rfftwnd_destroy_plan(d_plan_ctor_1);
    rfftwnd_destroy_plan(d_plan_ctor_2);
}