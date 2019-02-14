#include "main.ih"

//do_one_simulation_step: Do one complete cycle of the simulation:
//      - set_forces:
//      - solve:            read forces from the user
//      - diffuse_matter:   compute a new set of velocities
//      - gluPostRedisplay: draw a new visualization frame
void simulation_step(void)
{
	if (!frozen)
	{
	  set_forces();
	  solve(DIM, vx, vy, vx0, vy0, visc, dt);
	  diffuse_matter(DIM, vx, vy, rho, rho0, dt);
	  glutPostRedisplay();
	}
}
