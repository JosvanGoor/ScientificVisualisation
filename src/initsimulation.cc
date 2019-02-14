#include "main.ih"

//init_simulation: Initialize simulation data structures as a function of the grid size 'n'.
//                 Although the simulation takes place on a 2D grid, we allocate all data structures as 1D arrays,
//                 for compatibility with the FFTW numerical library.
void init_simulation(int n)
{
	int i; size_t dim;

	dim     = n * 2*(n/2+1)*sizeof(fftw_real);        //Allocate data structures
	// vx      = (fftw_real*) malloc(dim);
	// vy      = (fftw_real*) malloc(dim);
	// vx0     = (fftw_real*) malloc(dim);
	// vy0     = (fftw_real*) malloc(dim);
	dim     = n * n * sizeof(fftw_real);
	fx      = (fftw_real*) malloc(dim);
	fy      = (fftw_real*) malloc(dim);
	rho     = (fftw_real*) malloc(dim);
	rho0    = (fftw_real*) malloc(dim);
	plan_rc = rfftw2d_create_plan(n, n, FFTW_REAL_TO_COMPLEX, FFTW_IN_PLACE);
	plan_cr = rfftw2d_create_plan(n, n, FFTW_COMPLEX_TO_REAL, FFTW_IN_PLACE);

	for (i = 0; i < n * n; i++)                      //Initialize data structures to 0
	{ vx[i] = vy[i] = vx0[i] = vy0[i] = fx[i] = fy[i] = rho[i] = rho0[i] = 0.0f; }
}