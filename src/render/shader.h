#pragma once
#include <sstream>
#include "glSupport.h"

#define DEFINE_UNIFORM_FLOAT(type) \
    void setUnifor##type(char* name, const GLfloat* value) \
    { \
        GLuint location = glGetUniformLocation(t_program_id, name); \
        glUnifor##type(location, *value); \
    }

#define DEFINE_UNIFORM_VECTOR(type) \
    void setUnifor##type(char* name, const GLfloat *value) \
    { \
        GLuint location = glGetUniformLocation(t_program_id, name); \
        glUnifor##type(location, 1, value); \
    }

#define DEFINE_UNIFORM_MATRIX(type) \
    void setUnifor##type(char* name, const GLfloat *value) \
    { \
        GLuint location = glGetUniformLocation(t_program_id, name); \
        glUnifor##type(location, 1, GL_FALSE, value); \
    }

#define UNIFORM_SET(type, name, value) setUnifor##type(name, value)

#define MARCOIZE(option) "#define " #option

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

        struct shaderOption
        {
            bool COLOR;
            bool MATERIAL;
            bool TEXTURE;
            bool NORMAL;

            bool LIGHT;
            int L_DIRECTION;
            int L_POINT;
            int L_SPOT;

            bool CAST_SHADOW;
            bool RECV_SHADOW;
        };
        static shaderOption default_shader_option = {false, false, false, false, false, 0, 0, 0, false, false};

        static std::string option2macro(shaderOption option)
        {
            std::ostringstream marcos;
            if(option.COLOR) marcos << MARCOIZE(COLOR) << "\n";
            if(option.TEXTURE) marcos << MARCOIZE(TEXTURE) << "\n";
            if(option.NORMAL) marcos << MARCOIZE(NORMAL) << "\n";
            if(option.LIGHT) marcos << MARCOIZE(LIGHT) << "\n";
            if(option.CAST_SHADOW) marcos << MARCOIZE(CAST_SHADOW) << "\n";
            if(option.RECV_SHADOW) marcos << MARCOIZE(RECV_SHADOW) << "\n";

            marcos << MARCOIZE(L_DIRECTION) << " " << option.L_DIRECTION << "\n";
            marcos << MARCOIZE(L_POINT) << " " << option.L_POINT << "\n";
            marcos << MARCOIZE(L_SPOT) << " " << option.L_SPOT << "\n";
            return marcos.str();
        }

        class shader
        {
        private:
            GLuint t_shader_id;
            int t_succeed;
            int t_type;

        public:
            shader(char* path, int type, shaderOption option=default_shader_option);
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
           
        public:
            shaderOption t_option;

        public:
            shaderProgram();
            shaderProgram(shader vert, shader frag);
            shaderProgram(char* vert, char* frag, shaderOption option=default_shader_option);
            shaderProgram(const shaderProgram &s);
            ~shaderProgram();

            void linkShader();
            int isLoaded();
            void use();

            inline GLuint id() {return t_program_id;}

            DEFINE_UNIFORM_MATRIX(mMatrix4fv); //setUniformMatrix4fv
            DEFINE_UNIFORM_VECTOR(m2fv); // setUniform2fv
            DEFINE_UNIFORM_VECTOR(m3fv); // setUniform3fv
            DEFINE_UNIFORM_VECTOR(m4fv); // setUniform4fv
            DEFINE_UNIFORM_FLOAT(m1f); // setUniform1f
            DEFINE_UNIFORM_FLOAT(m1i); // setUniform1i

            void setUniform(char* name, uniformType utype, const float* value)
            {
                switch (utype)
                {
                case mMatrix4fv:
                    UNIFORM_SET(mMatrix4fv, name, value);
                    break;
                case m2fv:
                    UNIFORM_SET(m2fv, name, value);
                    break;
                case m3fv:
                    UNIFORM_SET(m3fv, name, value);
                    break;
                case m4fv:
                    UNIFORM_SET(m4fv, name, value);
                    break;
                case m1f:
                    UNIFORM_SET(m1f, name, value);
                    break;
                default:
                    break;
                }
            }
        };
    }
}