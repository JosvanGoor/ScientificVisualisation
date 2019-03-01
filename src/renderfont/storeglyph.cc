#include "renderfont.ih"

void RenderFont::store_glyph(FT_Face face, std::vector<unsigned char> &map, size_t mapwidth, size_t xpos, size_t ypos)
{
    size_t width = face->glyph->bitmap.width;
    size_t height = face->glyph->bitmap.rows;

    for (size_t row = 0; row < height; ++row)
    {
        for (size_t col = 0; col < width; ++col)
        {
            size_t current = row * width + col;
            size_t mapxy = (ypos + row) * mapwidth + (xpos + col);
            
            map[mapxy] = face->glyph->bitmap.buffer[current];
        }
    }
}