#include <string>
#include "shader.h"
#include "utils/fileUtils.h"

namespace ace
{
    namespace render
    {
        // ----------- shader -------------
        shader::shader(char* path, int type):t_type(type)
        {
            std::string file_str = ace::utils::readFile(path);
            const char* src_str = file_str.c_str();
            t_shader_id = glCreateShader(type);
            glShaderSource(t_shader_id, 1, &src_str, NULL);
            glCompileShader(t_shader_id);

            char infoLog[512];
            glGetShaderiv(t_shader_id, GL_COMPILE_STATUS, &t_succeed);
            if(!t_succeed)
            {
                glGetShaderInfoLog(t_shader_id, 512, NULL, infoLog);
                std::cout << "error on loading shader: " << infoLog << std::endl;
            }
        }

        shader::shader(const shader &s)
        {
            t_shader_id = s.t_shader_id;
            t_succeed = s.t_succeed;
        }

        shader::~shader()
        {
            glDeleteShader(t_shader_id);
        }

        GLuint shader::id()
        {
            return t_shader_id;
        }

        int shader::is_loaded()
        {
            return t_succeed;
        }

        // ----------- shaderProgram -------------
        shaderProgram::shaderProgram()
        {
        }

        shaderProgram::shaderProgram(shader vert, shader frag)
        {
            t_vert_id = vert.id();
            t_frag_id = frag.id();
            t_program_id = glCreateProgram();
            linkShader();
        }

        shaderProgram::shaderProgram(char* vert, char* frag)
        {
            shader vshader(vert, GL_VERTEX_SHADER);
            shader fshader(frag, GL_FRAGMENT_SHADER);
            t_vert_id = vshader.id();
            t_frag_id = fshader.id();
            t_program_id = glCreateProgram();
            linkShader();
        }

        shaderProgram::shaderProgram(const shaderProgram &s)
        {
            t_vert_id = s.t_vert_id;
            t_frag_id = s.t_frag_id;
            t_program_id = s.t_program_id;
            t_succeed = s.t_succeed;
        }

        shaderProgram::~shaderProgram()
        {
        }

        void shaderProgram::linkShader()
        {
            glAttachShader(t_program_id, t_vert_id);
            glAttachShader(t_program_id, t_frag_id);
            glLinkProgram(t_program_id);

            char infoLog[512];
            glGetProgramiv(t_program_id, GL_LINK_STATUS, &t_succeed);
            if(!t_succeed) {
                glGetProgramInfoLog(t_program_id, 512, NULL, infoLog);
                std::cout << "error on linking shader: " << infoLog << std::endl;
            }
        }

        int shaderProgram::is_loaded()
        {
            return t_succeed;
        }

        void shaderProgram::use()
        {
            glUseProgram(t_program_id);
        }
    }// render
}// ace

