#include "main.ih"

//visualize: This is the main visualization function
void visualize(void)
{
	int        i, j, idx; double px,py;
	fftw_real  wn = (fftw_real)winWidth / (fftw_real)(DIM + 1);   // Grid cell width
	fftw_real  hn = (fftw_real)winHeight / (fftw_real)(DIM + 1);  // Grid cell heigh

	if (draw_smoke)
	{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (j = 0; j < DIM - 1; j++)			//draw smoke
	{
		glBegin(GL_TRIANGLE_STRIP);

		i = 0;
		px = wn + (fftw_real)i * wn;
		py = hn + (fftw_real)j * hn;
		idx = (j * DIM) + i;
		glColor3f(rho[idx],rho[idx],rho[idx]);
		glVertex2f(px,py);

		for (i = 0; i < DIM - 1; i++)
		{
			px = wn + (fftw_real)i * wn;
			py = hn + (fftw_real)(j + 1) * hn;
			idx = ((j + 1) * DIM) + i;
			set_colormap(rho[idx]);
			glVertex2f(px, py);
			px = wn + (fftw_real)(i + 1) * wn;
			py = hn + (fftw_real)j * hn;
			idx = (j * DIM) + (i + 1);
			set_colormap(rho[idx]);
			glVertex2f(px, py);
		}

		px = wn + (fftw_real)(DIM - 1) * wn;
		py = hn + (fftw_real)(j + 1) * hn;
		idx = ((j + 1) * DIM) + (DIM - 1);
		set_colormap(rho[idx]);
		glVertex2f(px, py);
		glEnd();
	}
	}

	if (draw_vecs)
	{
	  glBegin(GL_LINES);				//draw velocities
	  for (i = 0; i < DIM; i++)
	    for (j = 0; j < DIM; j++)
	    {
		  idx = (j * DIM) + i;
		  direction_to_color(vx[idx],vy[idx],color_dir);
		  glVertex2f(wn + (fftw_real)i * wn, hn + (fftw_real)j * hn);
		  glVertex2f((wn + (fftw_real)i * wn) + vec_scale * vx[idx], (hn + (fftw_real)j * hn) + vec_scale * vy[idx]);
	    }
	  glEnd();
	}
}