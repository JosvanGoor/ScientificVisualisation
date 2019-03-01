#include "renderfont.ih"

pair<size_t, size_t> RenderFont::first_pass(FT_Face face)
{
    size_t height = 0;
    size_t width = 0;
    for (char row = 0; row < 8; ++row)
    {
        for (char col = 0; col < 16; ++col)
        {
            char current = row * 16 + col;
            if (FT_Load_Char(face, current, FT_LOAD_COMPUTE_METRICS))
            {
                cerr << "FreeType failed to load glyph: " 
                     << static_cast<int>(current) << "\n";
                continue;
            }
            width = max<size_t>(width, face->glyph->metrics.width >> 6);
            height = max<size_t>(height, face->glyph->metrics.height >> 6);
        }
    }
    return {width, height};
}