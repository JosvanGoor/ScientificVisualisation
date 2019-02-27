#ifndef __INCLUDED_TEXTRENDERMODEL_H
#define __INCLUDED_TEXTRENDERMODEL_H

#include <map>
#include <string>

#include <ft2build.h>
#include <freetype/freetype.h>

#include "../rendermodel/rendermodel.h"

struct Character
{
    GLuint texture_id;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint advance;
};

class TextRenderer
{
    size_t d_width;
    size_t d_height;

    GLuint d_program;
    GLuint d_buffer;
    GLuint d_attributes;
    GLuint d_color_location;
    GLuint d_sampler_location;

    std::map<GLubyte, Character> d_characters;

    public:
        TextRenderer(std::string const &font, size_t size);

        void render_string(std::string const &text, float xpos, float ypos, glm::vec3 color);

    private:
        void load_glyphs(std::string const &font, size_t size);
        void load_program();
        void load_buffers();
};

#endif