#include "globals.h"

//--- SIMULATION PARAMETERS ------------------------------------------------------------------------
const int DIM = 50;				//size of simulation grid
double dt = 0.4;				//simulation time step
float visc = 0.001;				//fluid viscosity
fftw_real *vx, *vy;             //(vx,vy)   = velocity field at the current moment
fftw_real *vx0, *vy0;           //(vx0,vy0) = velocity field at the previous moment
fftw_real *fx, *fy;	            //(fx,fy)   = user-controlled simulation forces, steered with the mouse
fftw_real *rho, *rho0;			//smoke density at the current (rho) and previous (rho0) moment
rfftwnd_plan plan_rc, plan_cr;  //simulation domain discretization


//--- VISUALIZATION PARAMETERS ---------------------------------------------------------------------
int   winWidth, winHeight;      //size of the graphics window, in pixels
int   color_dir = 0;            //use direction color-coding or not
float vec_scale = 1000;			//scaling of hedgehogs
int   draw_smoke = 0;           //draw the smoke or not
int   draw_vecs = 1;            //draw the vector field or not
const int COLOR_BLACKWHITE=0;   //different types of color mapping: black-and-white, rainbow, banded
const int COLOR_RAINBOW=1;
const int COLOR_BANDS=2;
int   scalar_col = 0;           //method for scalar coloring
int   frozen = 0;               //toggles on/off the animation