computational visualization repo

List of dependencies:
* fftw3
* GLFW (version 3)

This is build and tested with gcc version 8, which should contain everything required for OpenMP.

When running the program (./scivis) it might take a while for a window to pop up. This is because the program is then generating a wisdom file which greatly speeds up the fast fourier transform. This should only happen on the first time starting te program.

When running the program press 'H' to toggle a help display which shows the available options.

All code is available on the github repository found at:
https://github.com/JosvanGoor/ScientificVisualisation