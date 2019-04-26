#include "frame.h"
#include "interaction/log.h"

namespace ace
{
    namespace render
    {
        frame::frame()
        {
            glGenFramebuffers(1, &t_fbo);
            glGenRenderbuffers(1, &t_rbo);
        }
        
        frame::~frame()
        {
            glDeleteFramebuffers(1, &t_fbo);
            glDeleteRenderbuffers(1, &t_rbo);
        }

        void frame::attachTexture(GLuint tex, GLuint attach_type)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, t_fbo);
            glFramebufferTexture2D(GL_FRAMEBUFFER, attach_type, GL_TEXTURE_2D, tex, 0);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            t_attaches[attach_type] = tex;
        }

        void frame::attachRbo(GLuint rbo_type, GLuint attach_type)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, t_fbo);
            glBindRenderbuffer(GL_RENDERBUFFER, t_rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, rbo_type, 800, 600); 
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, attach_type, GL_RENDERBUFFER, t_rbo);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void frame::bind() {
            if (!isComplete()) {
                LOG_DEFAULT("error: framebuffer is not complete!");
            }
            else {
                glBindFramebuffer(GL_FRAMEBUFFER, t_fbo);
            }
        }

        GLuint frame::operator[](GLuint attach_type)
        {
            return t_attaches[attach_type];
        }
    }
}