#ifndef __UTILITY_H_
#define __UTILITY_H_

#include <string>
#include <vector>
#include <glad/glad.h>

constexpr double pi() { return 3.14159265359; }

inline int clamp(double val)
{
    return val >= 0.0
        ? static_cast<int>(val)
        : -static_cast<int>(1 - val);
}
std::string read_file(std::string const &file);

template <typename Data>
size_t bytesize(std::vector<Data> const &vec);

template <typename Num>
Num radians(Num deg);

template <typename Num>
Num degrees(Num rad);

float linterp(double *data, size_t range, size_t gridsize, size_t pivx, size_t pivy);

/*
    Opengl
*/

GLuint compile_shader(std::string const &source, GLuint type);
GLuint link_program(GLuint vshader, GLuint fshader);
GLuint build_program(std::string const &vfile, std::string const &ffile);
GLuint load_texture(std::string const &file);

/****
 * INLINES
 ****/
template <typename Data>
inline size_t bytesize(std::vector<Data> const &vec)
{
    return vec.size() * sizeof(Data);
}

template <typename Num>
inline Num radians(Num deg)
{
    return deg * pi() / 180.0;
}

template <typename Num>
inline Num degrees(Num rad)
{
    return rad * 180 / pi();
}

#endif