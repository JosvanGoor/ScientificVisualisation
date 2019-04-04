#include "window.ih"
#include <iostream>
#include <chrono>

void Window::repaint()
{
    if (omp_get_thread_num() == 0)
    {
        d_rendermodel->set_colormapping(static_cast<int>(d_colormapping));
        lines.resize(0);

        if (d_drawmode == DrawMode::SMOKE3D || d_drawmode == DrawMode::STREAMTUBES)
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
            case DrawMode::STREAMTUBES:
                stream_lines.clear();
                for (glm::vec3 const &anchor : d_streamline_anchors)
                {
                    calc_streamline
                    (
                        d_simulation.gridsize() * anchor.x,
                        d_simulation.gridsize() * anchor.y,
                        anchor.z * 200
                    );
                }
            
            // fallthrough
            case DrawMode::SMOKE:
            case DrawMode::SMOKE3D:
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
        // update scalar for smoke if applicable
        d_scalar_mode = d_heightmode;
    }

    #pragma omp barrier
    if (d_drawmode == DrawMode::SMOKE3D
            && d_heightmode != d_colormode)
    {
        // recalculate store for heightmapping
        calcStore();
    }

    // #pragma omp barrier
    if (omp_get_thread_num() == 0)
    {
        if (d_drawmode == DrawMode::SMOKE3D)
        {
            d_smoke3d.release_framebuffer();
            d_smoke3d.set_heightmap(store, v_min, v_max);
            d_smoke3d.render();
        }

        if (d_drawmode == DrawMode::STREAMTUBES)
        {
            d_smoke3d.release_framebuffer();
            
            // this is awefull and slow
            vector<float> zeros;
            zeros.resize(store.size(), 0.0f);

            d_smoke3d.set_heightmap(zeros, v_min, v_max);
            d_smoke3d.render();

            if (!d_streamline_anchors.empty())
                d_streamtubes.draw_lines(stream_lines, d_simulation.gridsize());
        }

        switch(d_glyphmode)
        {
            case GlyphMode::NONE:
                break;

            case GlyphMode::GLYPH:
                d_glyphs.update_vectors(d_simulation.vfield_x(), d_simulation.vfield_y(), d_simulation.gridsize());
                d_glyphs.update_scalar(d_simulation.rho(), d_simulation.gridsize());
                if (d_drawmode == DrawMode::SMOKE3D || d_drawmode == DrawMode::STREAMTUBES)
                    d_glyphs.render();
                else
                    d_glyphs.render_2d();
            break;

            case GlyphMode::ARROW:
                d_arrows.update_vectors(d_simulation.vfield_x(), d_simulation.vfield_y(), d_simulation.gridsize());
                d_arrows.update_scalar(d_simulation.rho(), d_simulation.gridsize());
                if (d_drawmode == DrawMode::SMOKE3D || d_drawmode == DrawMode::STREAMTUBES)
                    d_arrows.render();
                else
                    d_arrows.render_2d();
            break;

            default:
                throw "Wtf this is impossible..."s;
        }

        SmokeRenderModel *mdl = dynamic_cast<SmokeRenderModel*>(d_rendermodel.get());
        if (mdl)
            mdl->render_bar();

        if (d_help)
        {
            float xpos = d_width / 2 - d_helpstring.width() / 2;
            float ypos = d_height / 2 - d_helpstring.height() / 2;
            cout << "xpos: " << xpos << " ypos: " << ypos << "\n";
            d_helpfont.render_string_outlined(d_helpstring, glm::vec2(200, 200));
        }

    }
    //DO NOT ADD OMP BARRIER HERE!!!
}