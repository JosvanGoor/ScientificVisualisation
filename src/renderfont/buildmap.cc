#include "renderfont.ih"

vector<unsigned char> RenderFont::build_map(FT_Face face, size_t width, size_t height)
{
    vector<unsigned char> map;

    map.resize((width * 8) * (height * 16), 0.0f);

    for (size_t row = 0; row < 8; ++row)
    {
        size_t curh = height * row;
        for (size_t col = 0; col < 16; ++col)
        {
            size_t current = row * 16 + col;
            size_t curw = col * width;

            if (FT_Load_Char(face, current, FT_LOAD_RENDER))
            {
                d_characters.push_back({});
                continue;
            }

            size_t glyph_width = face->glyph->bitmap.width;
            size_t glyph_height = face->glyph->bitmap.rows;

            d_characters.push_back( 
            {
                glm::vec2{glyph_width, glyph_height},
                glm::vec2{face->glyph->bitmap_left, face->glyph->bitmap_top},
                tex_position(width * 16, height * 8, curw, curh),
                tex_position(width * 16, height * 8, curw + glyph_width, curh + glyph_height),
                static_cast<size_t>(face->glyph->advance.x >> 6)
            });

            store_glyph(face, map, width * 16, curw, curh);
        }   
    }

    return map;
}