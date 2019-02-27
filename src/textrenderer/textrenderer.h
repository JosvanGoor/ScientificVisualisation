#ifndef __INCLUDED_TEXTRENDERMODEL_H
#define __INCLUDED_TEXTRENDERMODEL_H

#include <map>
#include <string>

#include <ft2build.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    GLuint d_color_location;
    GLuint d_sampler_location;

    std::map<GLubyte, Character> d_characters;

    public:
        TextRenderer(std::string const &font, size_t size);

    private:
        void load_glyphs(std::string const &font, size_t size);
};

#endif