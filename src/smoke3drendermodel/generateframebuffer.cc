#include "smoke3drendermodel.ih"

void Smoke3dRenderModel::generate_framebuffer()
{
    if (d_framebuffer)   
    {
        glDeleteFramebuffers(1, &d_framebuffer);
        glDeleteTextures(1, &d_color_tex);
        glDeleteRenderbuffers(1, &d_depth_rbuf);
    }
    
    glGenFramebuffers(1, &d_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, d_framebuffer);

    glGenTextures(1, &d_color_tex);
    glBindTexture(GL_TEXTURE_2D, d_color_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, d_width, d_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, d_color_tex, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &d_depth_rbuf);
    glBindRenderbuffer(GL_RENDERBUFFER, d_depth_rbuf);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, d_width, d_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, d_depth_rbuf);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw "Framebuffer incomplete =("s;

    GLenum buffers[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, buffers);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}