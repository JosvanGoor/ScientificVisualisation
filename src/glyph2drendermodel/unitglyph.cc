#include "glyph2drendermodel.ih"

vector<float> Glyph2dRenderModel::unit_glyph()
{
    return
    {
        -1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f,  0.0f
    };
}