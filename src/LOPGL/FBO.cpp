#include "FBO.h"
#include <iostream>

using namespace hdgbdn;
using namespace std;

void FBO::BindFBO(const FBO& fbo)
{
    glBindFramebuffer(GL_FRAMEBUFFER, *fbo.pFrameBufferID);
}

void FBO::UnBindFBO(const FBO& fbo)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FBO::FBO(const int w, const int h)
{
    pFrameBufferID = shared_ptr<unsigned int>(0, [](unsigned int* id)
        {
    		// when a frame buffer id use count decreased to 0, delete it in OpenGL
            glDeleteFramebuffers(1, id);
        });
    glGenFramebuffers(1, pFrameBufferID.get());
    glBindFramebuffer(GL_FRAMEBUFFER, *pFrameBufferID);
    // create a color attachment texture
    unsigned int textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
