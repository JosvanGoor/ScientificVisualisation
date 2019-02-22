#include "main.ih"

size_t window_width = 500;
size_t window_height = 500;

int main(int argc, char *argv[])
{

    Simulation simulation;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("GLUT IS A TRASH LIBRARY");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(drag);
}