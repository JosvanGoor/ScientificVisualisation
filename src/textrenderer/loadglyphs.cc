#include "textrenderer.ih"

#include <iostream>

void TextRenderer::load_glyphs(string const &font, size_t size)
{
    // fire up freetype
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        throw "Failed to initialize freetype"s;

    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face))
        throw "Freetype failed to load font face"s;

    FT_Set_Pixel_Sizes(face, 0, size);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (GLubyte ch = 0; ch < 128; ++ch)
    {
        if (FT_Load_Char(face, ch, FT_LOAD_RENDER))
        {
            cout << "Failed to load glyph: " << static_cast<int>(ch) << "\n";
            continue;
        }

        GLuint texture;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D
        (
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        d_characters.insert(pair<GLchar, Character>
        {
            ch,
            {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<GLuint>(face->glyph->advance.x)
            }
        });
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}