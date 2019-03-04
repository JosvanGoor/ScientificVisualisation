#ifndef __INCLUDED_OBJREADER_H
#define __INCLUDED_OBJREADER_H

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Index
{
    int vertex;
    int normal;
    int texcoord;
};

typedef std::vector<Index> Face;

struct Vertex
{
    glm::vec3 d_position;
    glm::vec2 d_texcoords;
    glm::vec3 d_normal;
};

struct Triangle
{
    Vertex p1;
    Vertex p2;
    Vertex p3;
};

class ObjReader
{
    std::vector<glm::vec3> d_vertices;
    std::vector<glm::vec3> d_normals;
    std::vector<glm::vec3> d_texcoords;
    std::vector<Face> d_faces;

    public:
        ObjReader(std::string const &file);

        std::vector<Triangle> extract_triangles();
        std::vector<float> raw_vertices();
        std::vector<float> raw_normals();

    private:
        Vertex extract_vertex(Index const &index);

        Index parse_index(std::string const &text);
        void parse_face(std::string const &line);
        void parse_vertex(std::string const &line);
        void parse_normal(std::string const &line);
};

#endif