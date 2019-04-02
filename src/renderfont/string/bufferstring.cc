#include "string.ih"

#include <iostream>

void RenderFont::String::buffer_string(string const &str, vector<Character> const &characters)
{
    vector<float> buffer;
    buffer.reserve(str.size() * 6 * 4);

    size_t width = 0;
    size_t xpos = 0;
    size_t ypos = 0;
    d_drawcount = 0;
    for (char ch : str)
    {
        if (ch == ' ')
        {
            xpos += characters[' '].advance;
            continue;
        }

        if (ch == '\n')
        {
            xpos = 0;
            ypos += characters['I'].size.y * 1.25 + 4;
            continue;
        }



        float xp = xpos + characters[ch].bearing.x;
        float yp = ypos + -characters[ch].bearing.y + d_height;
        float w = characters[ch].size.x;
        float h = characters[ch].size.y;

        float tex_x0 = characters[ch].tex_topleft.x;
        float tex_x1 = characters[ch].tex_botright.x;
        float tex_y0 = characters[ch].tex_botright.y;
        float tex_y1 = characters[ch].tex_topleft.y;

        buffer.insert(buffer.end(),
        {
            xp,     yp + h,     tex_x0, tex_y0,
            xp,     yp,         tex_x0, tex_y1,
            xp + w, yp,         tex_x1, tex_y1,
            xp,     yp + h,     tex_x0, tex_y0,
            xp + w, yp,         tex_x1, tex_y1,
            xp + w, yp + h,     tex_x1, tex_y0
        });

        d_drawcount += 6;
        xpos += characters[ch].advance;

        d_width = max(d_width, xpos);
    }

    d_height = ypos;
    glBindBuffer(GL_ARRAY_BUFFER, d_buffer);
    glBufferData(GL_ARRAY_BUFFER, bytesize(buffer), buffer.data(), d_storage_mode);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}