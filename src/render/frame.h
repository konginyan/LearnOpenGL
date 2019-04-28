#pragma once
#include <unordered_map>
#include "glSupport.h"

namespace ace
{
    namespace render
    {
        class frame
        {
        private:
            GLuint t_fbo;
            GLuint t_rbo;

        public:
            std::unordered_map<GLuint, GLuint> t_attaches; // attach_type, texture_id

        public:
            frame();
            frame(frame& f) = delete;
            ~frame();

            void attachTexture(GLuint tex, GLuint attach_type);
            void attachRbo(GLuint rbo_type, GLuint attach_type);
            bool isComplete() {return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;}
            GLuint operator[](GLuint attach_type);

            void bind();

            inline GLuint id() {return t_fbo;}
        };
    }
}