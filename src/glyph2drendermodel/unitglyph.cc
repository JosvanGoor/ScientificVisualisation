#include "glyph2drendermodel.ih"

vector<float> Glyph2DRenderModel::unit_glyph()
{
    return
    {
        -1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f,  0.0f
    };
}