#include "glyph2drendermodel.ih"

vector<float> Glyph2dRenderModel::unit_glyph()
{
    // return
    // {
    //     -2.5f,  1.0f,
    //     -2.5f, -1.0f,
    //      2.5f,  0.0f
    // };

    return
    {
        -0.25f, 0.1f,
        -0.25f, -0.1f,
        0.25f, 0.0f
    };
}