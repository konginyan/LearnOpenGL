#pragma once
#include <string>
#include "glSupport.h"

#define DEFINE_UNIFORM_FLOAT(type) \
    void setUnifor##type(const char* name, const GLfloat* value) \
    { \
        GLuint location = glGetUniformLocation(t_program_id, name); \
        glUnifor##type(location, *value); \
    }

#define DEFINE_UNIFORM_VECTOR(type) \
    void setUnifor##type(const char* name, const GLfloat *value) \
    { \
        GLuint location = glGetUniformLocation(t_program_id, name); \
        glUnifor##type(location, 1, value); \
    }

#define DEFINE_UNIFORM_MATRIX(type) \
    void setUnifor##type(const char* name, const GLfloat *value) \
    { \
        GLuint location = glGetUniformLocation(t_program_id, name); \
        glUnifor##type(location, 1, GL_FALSE, value); \
    }

#define UNIFORM_SET(type, name, value) setUnifor##type(name, value)

namespace ace
{
    namespace render
    {
        enum uniformType
        {
            mMatrix4fv,
            m2fv,
            m3fv,
            m4fv,
            m1f,
            m1i
        };

        class shader
        {
        private:
            GLuint t_program_id;
            GLuint t_vert_id;
            GLuint t_frag_id;
            std::string t_vert_str;
            std::string t_frag_str;

        public:
            bool t_linked;

        public:
            shader();
            shader(const char* vert, const char* frag);
            shader(const shader &s) = delete;
            ~shader();

            void setMarco(char* marco);
            void compileAndLink();
            void use();

            inline GLuint id() {return t_program_id;}

            DEFINE_UNIFORM_MATRIX(mMatrix4fv); //setUniformMatrix4fv
            DEFINE_UNIFORM_VECTOR(m2fv); // setUniform2fv
            DEFINE_UNIFORM_VECTOR(m3fv); // setUniform3fv
            DEFINE_UNIFORM_VECTOR(m4fv); // setUniform4fv
            DEFINE_UNIFORM_FLOAT(m1f); // setUniform1f
            DEFINE_UNIFORM_FLOAT(m1i); // setUniform1i

            void setUniform(std::string name, uniformType utype, const float* value)
            {
                switch (utype)
                {
                case mMatrix4fv:
                    UNIFORM_SET(mMatrix4fv, name.c_str(), value);
                    break;
                case m2fv:
                    UNIFORM_SET(m2fv, name.c_str(), value);
                    break;
                case m3fv:
                    UNIFORM_SET(m3fv, name.c_str(), value);
                    break;
                case m4fv:
                    UNIFORM_SET(m4fv, name.c_str(), value);
                    break;
                case m1f:
                    UNIFORM_SET(m1f, name.c_str(), value);
                    break;
                case m1i:
                    UNIFORM_SET(m1i, name.c_str(), value);
                    break;
                default:
                    break;
                }
            }
        };
    }
}