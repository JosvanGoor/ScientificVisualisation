#include "window.ih"
#include <iostream>
#include <chrono>

void Window::repaint()
{
    if (!d_rendermodel)
    {
        cerr << "No current rendermodel! skipping draw.\n";
        return;
    }

    if (omp_get_thread_num() == 0)
    {
        d_rendermodel->set_colormapping(static_cast<int>(d_colormapping));
    }

    calcStore();

    #pragma omp barrier
    if (omp_get_thread_num() == 0)
    {
        switch(d_drawmode)
        {
            case DrawMode::SMOKE:
                paint_smoke();
            break;

            case DrawMode::VECTORS:
                    paint_vectors();
            break;

            case DrawMode::NONE:
                return;

            default:
                throw "Wtf this is impossible..."s;
        }

        switch(d_glyphmode)
        {
            case GlyphMode::NONE:
                break;

            case GlyphMode::GLYPH:
                d_glyphs.update_vectors(d_simulation.vfield_x(), d_simulation.vfield_y(), d_simulation.gridsize());
                d_glyphs.update_scalar(d_simulation.rho(), d_simulation.gridsize());
                d_glyphs.render();
            break;

            case GlyphMode::ARROW:
                d_arrows.update_vectors(d_simulation.vfield_x(), d_simulation.vfield_y(), d_simulation.gridsize());
                d_arrows.update_scalar(d_simulation.rho(), d_simulation.gridsize());
                d_arrows.render();
            break;

            default:
                throw "Wtf this is impossible..."s;
        }

        SmokeRenderModel *mdl = dynamic_cast<SmokeRenderModel*>(d_rendermodel.get());
        if (mdl)
            mdl->render_bar();
    }

    //DO NOT ADD OMP BARRIER HERE!!!

}