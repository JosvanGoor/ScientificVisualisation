#include <rfftw.h>              //the numerical simulation FFTW library

//--- SIMULATION PARAMETERS ------------------------------------------------------------------------
extern const int DIM;				//size of simulation grid
extern double dt;				//simulation time step
extern float visc;				//fluid viscosity
extern fftw_real *vx, *vy;             //(vx,vy)   = velocity field at the current moment
extern fftw_real *vx0, *vy0;           //(vx0,vy0) = velocity field at the previous moment
extern fftw_real *fx, *fy;	            //(fx,fy)   = user-controlled simulation forces, steered with the mouse
extern fftw_real *rho, *rho0;			//smoke density at the current (rho) and previous (rho0) moment
extern rfftwnd_plan plan_rc, plan_cr;  //simulation domain discretization


//--- VISUALIZATION PARAMETERS ---------------------------------------------------------------------
extern int   winWidth, winHeight;      //size of the graphics window, in pixels
extern int   color_dir;            //use direction color-coding or not
extern float vec_scale;			//scaling of hedgehogs
extern int   draw_smoke;           //draw the smoke or not
extern int   draw_vecs;            //draw the vector field or not
extern const int COLOR_BLACKWHITE;   //different types of color mapping: black-and-white, rainbow, banded
extern const int COLOR_RAINBOW;
extern const int COLOR_BANDS;
extern int   scalar_col;           //method for scalar coloring
extern int   frozen;               //toggles on/off the animation