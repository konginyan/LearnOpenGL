#pragma once
#include "glSupport.h"

#define DEFINE_UNIFORM_VECTOR(type) \
    void setUniform##type(char* name, GLsizei count, GLfloat *value) \
    { \
        GLuint location = glGetUniformLocation(t_program_id, name); \
        glUniform##type(location, count, value); \
    }

#define DEFINE_UNIFORM_MATRIX(type) \
    void setUniform##type(char* name, GLsizei count, GLboolean transpose, GLfloat *value) \
    { \
        GLuint location = glGetUniformLocation(t_program_id, name); \
        glUniform##type(location, count, transpose, value); \
    }

namespace ace
{
    namespace render
    {
        class shader
        {
        private:
            GLuint t_shader_id;
            int t_succeed;
            int t_type;

        public:
            shader(char* path, int type);
            shader(const shader &s);
            ~shader();

            GLuint id();
            int is_loaded();
        };

        class shaderProgram
        {
        private:
            GLuint t_program_id;
            GLuint t_vert_id;
            GLuint t_frag_id;
            int t_succeed;

        public:
            shaderProgram();
            shaderProgram(shader vert, shader frag);
            shaderProgram(char* vert, char* frag);
            shaderProgram(const shaderProgram &s);
            ~shaderProgram();

            void linkShader();
            int is_loaded();
            void use();

            DEFINE_UNIFORM_MATRIX(Matrix4fv); //setUniformMatrix4fv
        };
    }// render
}// ace