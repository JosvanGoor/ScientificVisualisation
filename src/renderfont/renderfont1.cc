#include "renderfont.ih"

RenderFont::RenderFont(string const &file, size_t size)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        throw "Failed to initialize FreeType"s;

    FT_Face face;
    if (FT_New_Face(ft, file.c_str(), 0, &face))
        throw "FreeType failed to load file: "s + file;

    FT_Set_Pixel_Sizes(face, 0, size);

    auto [charw, charh] = first_pass(face);
    vector<unsigned char> map = build_map(face, charw, charh);
    generate_texture(map, charw * 16, charh * 8);

    d_size = size;
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    d_program = build_program
    (
        "shaders/fontvshader.glsl",
        "shaders/fontfshader.glsl"
    );

    d_projection = glm::ortho(0.0f, 100.0f, 100.0f, 0.0f);
    d_transform_loc = glGetUniformLocation(d_program, "projection");
    d_position_loc = glGetUniformLocation(d_program, "translation");
    d_color_loc = glGetUniformLocation(d_program, "text_color");
}