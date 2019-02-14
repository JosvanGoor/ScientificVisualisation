#include "main.ih"

//keyboard: Handle key presses
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	  case 't': dt -= 0.001; break;
	  case 'T': dt += 0.001; break;
	  case 'c': color_dir = 1 - color_dir; break;
	  case 'S': vec_scale *= 1.2; break;
	  case 's': vec_scale *= 0.8; break;
	  case 'V': visc *= 5; break;
	  case 'v': visc *= 0.2; break;
	  case 'x': draw_smoke = 1 - draw_smoke;
		    if (draw_smoke==0) draw_vecs = 1; break;
	  case 'y': draw_vecs = 1 - draw_vecs;
		    if (draw_vecs==0) draw_smoke = 1; break;
	  case 'm': scalar_col++; if (scalar_col>COLOR_BANDS) scalar_col=COLOR_BLACKWHITE; break;
	  case 'a': frozen = 1-frozen; break;
	  case 'q': exit(0);
	}
}