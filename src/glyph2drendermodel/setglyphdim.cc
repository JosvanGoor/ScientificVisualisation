#include "glyph2drendermodel.ih"

void Glyph2dRenderModel::set_glyph_dim(size_t dim)
{
    d_glyph_dim = dim;

    d_coord_advance = 
        static_cast<float>(250) / static_cast<float>(d_glyph_dim);
    d_coord_start = d_coord_advance / 2.0f;   
}