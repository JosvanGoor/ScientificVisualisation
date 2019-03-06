#include "enums.ih"

string glyphmode_string(GlyphMode mapping)
{
    switch(mapping)
    {
        case GlyphMode::NONE:
            return "GlyphMode::NONE";
        
        case GlyphMode::GLYPH:
            return "GlyphMode::2D_ARROW";

        case GlyphMode::ARROW:
            return "GlyphMode::3D_ARROW";
        default:
            return "Unknown or Modval ColorMapping";
    }
}