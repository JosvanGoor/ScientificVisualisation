#include "utility.ih"

#include <iostream>

GLuint load_texture(string const &file)
{
    vector<unsigned char> image_data;
    unsigned int width, height;
    size_t error = lodepng::decode(image_data, width, height, file.c_str());

    if (error != 0)
    {
        stringstream ss;
        ss << "Error loading texture: " << lodepng_error_text(error);
        throw ss.str();
    }

    cout << "texture size: [" << width << ", " << height << "]\n";

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return texture;
}