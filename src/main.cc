#include "main.ih"

int main(int argc, char *argv[])
{
    cout << "Fluid Flow Simulation and Visualization\n";
	cout << "=======================================\n";
	cout << "Click and drag the mouse to steer the flow!\n";
	cout << "T/t:   increase/decrease simulation timestep\n";
	cout << "S/s:   increase/decrease hedgehog scaling\n";
	cout << "c:     toggle direction coloring on/off\n";
	cout << "V/v:   increase decrease fluid viscosity\n";
	cout << "x:     toggle drawing matter on/off\n";
	cout << "y:     toggle drawing hedgehogs on/off\n";
	cout << "m:     toggle thru scalar coloring\n";
	cout << "a:     toggle the animation on/off\n";
	cout << "q:     quit\n\n";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutCreateWindow("Real-time smoke simulation and visualization");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(simulation_step);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(drag);

	init_simulation(DIM);	//initialize the simulation data structures
	glutMainLoop();			//calls do_one_simulation_step, keyboard, display, drag, reshape
	return 0;
}