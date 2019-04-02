#ifndef __INCLUDED_RENDERFONT_STRING_H
#define __INCLUDED_RENDERFONT_STRING_H

#include "../renderfont.h"

class RenderFont::String
{
    friend class RenderFont;

    GLuint d_vao;
    GLuint d_buffer;
    GLuint d_storage_mode;
    glm::vec3 d_color;
    glm::vec3 d_outline_color;
    size_t d_drawcount;

    size_t d_width;
    size_t d_height;
    std::string d_text;

    public:
        String();
        ~String();
        String(String &&move);
        String &operator=(String &&move);
        void swap(String &other);

        size_t width() const;
        size_t height() const;
        std::string text() const;

        void set_text_color(glm::vec3 color);
        void set_outline_color(glm::vec3 color);

    private:
        String(GLuint store_mode, size_t height);
        String(String const &copy) = delete;
        String &operator=(String const &copy) = delete;

        void generate_buffers();
        void buffer_string(std::string const &str, std::vector<Character> const &characters);
};

inline RenderFont::String::String()
{
    d_vao = 0;
}

inline size_t RenderFont::String::width() const
{
    return d_width;
}

inline size_t RenderFont::String::height() const
{
    return d_height;
}

inline void RenderFont::String::set_text_color(glm::vec3 color)
{
    d_color = color;
}

inline void RenderFont::String::set_outline_color(glm::vec3 color)
{
    d_outline_color = color;
}

#endif