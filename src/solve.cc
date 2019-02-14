#include "main.ih"

//solve: Solve (compute) one step of the fluid flow simulation
void solve(int n, fftw_real* vx, fftw_real* vy, fftw_real* vx0, fftw_real* vy0, fftw_real visc, fftw_real dt)
{
	fftw_real x, y, x0, y0, f, r, U[2], V[2], s, t;
	int i, j, i0, j0, i1, j1;

	for (i=0;i<n*n;i++)
	{ vx[i] += dt*vx0[i]; vx0[i] = vx[i]; vy[i] += dt*vy0[i]; vy0[i] = vy[i]; }

	for ( x=0.5f/n,i=0 ; i<n ; i++,x+=1.0f/n )
	   for ( y=0.5f/n,j=0 ; j<n ; j++,y+=1.0f/n )
	   {
	      x0 = n*(x-dt*vx0[i+n*j])-0.5f;
	      y0 = n*(y-dt*vy0[i+n*j])-0.5f;
	      i0 = clamp(x0); s = x0-i0;
	      i0 = (n+(i0%n))%n;
	      i1 = (i0+1)%n;
	      j0 = clamp(y0); t = y0-j0;
	      j0 = (n+(j0%n))%n;
	      j1 = (j0+1)%n;
	      vx[i+n*j] = (1-s)*((1-t)*vx0[i0+n*j0]+t*vx0[i0+n*j1])+s*((1-t)*vx0[i1+n*j0]+t*vx0[i1+n*j1]);
	      vy[i+n*j] = (1-s)*((1-t)*vy0[i0+n*j0]+t*vy0[i0+n*j1])+s*((1-t)*vy0[i1+n*j0]+t*vy0[i1+n*j1]);
	   }

	for(i=0; i<n; i++)
	  for(j=0; j<n; j++)
	  {  vx0[i+(n+2)*j] = vx[i+n*j]; vy0[i+(n+2)*j] = vy[i+n*j]; }

	FFT(1,vx0);
	FFT(1,vy0);

	for (i=0;i<=n;i+=2)
	{
	   x = 0.5f*i;
	   for (j=0;j<n;j++)
	   {
	      y = j<=n/2 ? (fftw_real)j : (fftw_real)j-n;
	      r = x*x+y*y;
	      if ( r==0.0f ) continue;
	      f = (fftw_real)exp(-r*dt*visc);
	      U[0] = vx0[i  +(n+2)*j]; V[0] = vy0[i  +(n+2)*j];
	      U[1] = vx0[i+1+(n+2)*j]; V[1] = vy0[i+1+(n+2)*j];

	      vx0[i  +(n+2)*j] = f*((1-x*x/r)*U[0]     -x*y/r *V[0]);
	      vx0[i+1+(n+2)*j] = f*((1-x*x/r)*U[1]     -x*y/r *V[1]);
	      vy0[i+  (n+2)*j] = f*(  -y*x/r *U[0] + (1-y*y/r)*V[0]);
	      vy0[i+1+(n+2)*j] = f*(  -y*x/r *U[1] + (1-y*y/r)*V[1]);
	   }
	}

	FFT(-1,vx0);
	FFT(-1,vy0);

	f = 1.0/(n*n);
 	for (i=0;i<n;i++)
	   for (j=0;j<n;j++)
	   { vx[i+n*j] = f*vx0[i+(n+2)*j]; vy[i+n*j] = f*vy0[i+(n+2)*j]; }
}