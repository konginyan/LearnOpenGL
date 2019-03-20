#pragma once
#include "glSupport.h"

#define DEFINE_UNIFORM_VECTOR(type) \
    void setUniform##type(char* name, const GLfloat *value) \
    { \
        GLuint location = glGetUniformLocation(t_program_id, name); \
        glUniform##type(location, 1, value); \
    }

#define DEFINE_UNIFORM_MATRIX(type) \
    void setUniform##type(char* name, const GLfloat *value) \
    { \
        GLuint location = glGetUniformLocation(t_program_id, name); \
        glUniform##type(location, 1, GL_FALSE, value); \
    }

#define MARCOIZE(option) "#define " #option "\n"

namespace ace
{
    namespace render
    {
        struct shaderOption
        {
            bool COLOR;
            bool MATERIAL;
            bool TEXTURE;
            bool NORMAL;

            bool LIGHT;
            bool L_DIRECTION;
            bool L_POINT;
            bool L_SPOT;

            bool CAST_SHADOW;
            bool RECV_SHADOW;
        };
        static shaderOption default_option = {false, false, false, false, false, false, false};

        static std::string option2macro(shaderOption option)
        {
            std::string marcos("");
            if(option.COLOR) marcos.append(MARCOIZE(COLOR));
            if(option.TEXTURE) marcos.append(MARCOIZE(TEXTURE));
            if(option.LIGHT) marcos.append(MARCOIZE(LIGHT));
            if(option.NORMAL) marcos.append(MARCOIZE(NORMAL));
            if(option.CAST_SHADOW) marcos.append(MARCOIZE(CAST_SHADOW));
            if(option.RECV_SHADOW) marcos.append(MARCOIZE(RECV_SHADOW));
            return marcos;
        }

        class shader
        {
        private:
            GLuint t_shader_id;
            int t_succeed;
            int t_type;

        public:
            shader(char* path, int type, shaderOption option=default_option);
            shader(const shader &s);
            ~shader();

            int is_loaded();

            inline GLuint id() {return t_shader_id;}
        };

        class shaderProgram
        {
        private:
            GLuint t_program_id;
            GLuint t_vert_id;
            GLuint t_frag_id;
            int t_succeed;
            shaderOption t_option;

        public:
            shaderProgram();
            shaderProgram(shader vert, shader frag);
            shaderProgram(char* vert, char* frag, shaderOption option=default_option);
            shaderProgram(const shaderProgram &s);
            ~shaderProgram();

            void linkShader();
            int is_loaded();
            void use();

            inline GLuint id() {return t_program_id;}

            DEFINE_UNIFORM_MATRIX(Matrix4fv); //setUniformMatrix4fv
            DEFINE_UNIFORM_VECTOR(2fv); // setUniform2fv
            DEFINE_UNIFORM_VECTOR(3fv); // setUniform3fv
            DEFINE_UNIFORM_VECTOR(4fv); // setUniform4fv
            
            void setUniform1f(char* name, GLfloat value)
            {
                GLuint location = glGetUniformLocation(t_program_id, name);
                glUniform1f(location, value);
            }
        };
    }
}