#ifndef __INCLUDED_RENDERFONT_H
#define __INCLUDED_RENDERFONT_H

#include <string>
#include <vector>

#include <ft2build.h>
#include <freetype/freetype.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../utility/utility.h"

/*
    RenderFont class
*/
class RenderFont
{
    struct Character;
    GLuint d_program;
    glm::mat4 d_projection;
    GLuint d_transform_loc;
    GLuint d_position_loc;
    GLuint d_color_loc;

    size_t d_size;
    GLuint d_charmap;
    std::vector<Character> d_characters;

    public:
        class String;

        RenderFont();
        RenderFont(std::string const &font, size_t size);
        RenderFont(RenderFont &&other);
        ~RenderFont();
        RenderFont &operator=(RenderFont &&other);
        void swap(RenderFont &other);

        bool valid() const;
        void set_size(size_t width, size_t height);

        String create_string(std::string const &text, GLuint storage_mode = GL_DYNAMIC_DRAW);
        void update_string(String &str, std::string const &text);
        void render_string(String const &str, glm::vec2 const &position);
        void render_string_outlined(String const &str, glm::vec2 const &position);
        
    private:
        std::pair<size_t, size_t> first_pass(FT_Face face);
        std::vector<unsigned char> build_map(FT_Face face, size_t width, size_t height);
        void generate_texture(std::vector<unsigned char> const &pixels, size_t width, size_t height);

        glm::vec2 tex_position(size_t width, size_t height, size_t xpos, size_t ypos);
        void store_glyph(FT_Face face, std::vector<unsigned char> &map, size_t mapwidth, size_t xpos, size_t ypos);
};

inline RenderFont::RenderFont()
{
    d_program = 0;
}

inline bool RenderFont::valid() const
{
    return d_program;
}

inline RenderFont &RenderFont::operator=(RenderFont &&other)
{
    swap(other);
    return *this;
}

inline void RenderFont::set_size(size_t width, size_t height)
{
    d_projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 0.0f);
}

/*
    RenderFont::Character struct
*/

struct RenderFont::Character
{
    glm::vec2 size;
    glm::vec2 bearing;
    glm::vec2 tex_topleft;
    glm::vec2 tex_botright;
    size_t advance;
};

// down here cuz circular poop
#include "string/string.h"

#endif