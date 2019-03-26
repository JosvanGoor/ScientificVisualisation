#include "window.ih"
#include <iostream>
#include <chrono>

void Window::repaint()
{
    // if (!d_rendermodel)
    // {
    //     cerr << "No current rendermodel! skipping draw.\n";
    //     return;
    // }

    if (omp_get_thread_num() == 0)
    {
        d_rendermodel->set_colormapping(static_cast<int>(d_colormapping));
        lines.resize(0);

        if (d_drawmode == DrawMode::SMOKE)
            d_smoke3d.bind_framebuffer();
        
        d_scalar_mode = d_colormode;
    }

    #pragma omp barrier
    calcStore();
    
    #pragma omp barrier
    
    if (d_isomode == IsolineMode::ISO2D)
    {   
        for (size_t idx = 0; idx != d_n_iso; ++idx)
        {
            calc_lines(d_iso_min + (idx + 1) * (d_iso_max - d_iso_min) / (d_n_iso + 1));
        }
    }

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

        if (d_colormode == ColorMode::DENSITY)
        {    
            switch(d_isomode)
            {
                case IsolineMode::ISO2D:
                    d_iso2d.update_lines(lines);
                    d_iso2d.render();
                break;

                case IsolineMode::OFF:
                break;

                default:
                    throw "Wtf this is impossible...";
            }
        }

        if (d_drawmode == DrawMode::SMOKE)
        {
            d_smoke3d.release_framebuffer();

            if (d_scalingmode == ScalingMode::DYNAMIC)
                d_smoke3d.set_heightmap(store, v_min, v_max);
            else
                d_smoke3d.set_heightmap(store, d_min, d_max);

            d_smoke3d.render();
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