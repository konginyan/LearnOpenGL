#include <string>
#include "shader.h"
#include "interaction/log.h"
#include "utils/fileUtils.h"

namespace ace
{
    namespace render
    {
        // ----------- shader -------------
        shader::shader(char* path, int type, shaderOption option):t_type(type)
        {
            std::string file_str = ace::utils::readFile(path);
            int first_line_end = file_str.find_first_of("\n");
            std::string options = option2macro(option);
            file_str.insert(first_line_end + 1, options);
            const char* src_str = file_str.c_str();

            t_shader_id = glCreateShader(type);
            glShaderSource(t_shader_id, 1, &src_str, NULL);
            glCompileShader(t_shader_id);

            char infoLog[512];
            glGetShaderiv(t_shader_id, GL_COMPILE_STATUS, &t_succeed);
            if(!t_succeed)
            {
                glGetShaderInfoLog(t_shader_id, 512, NULL, infoLog);
                LOG_DEFAULT("error on loading shader: %s\n", infoLog);
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

        shaderProgram::shaderProgram(char* vert, char* frag, shaderOption option)
        {
            shader vshader(vert, GL_VERTEX_SHADER, option);
            shader fshader(frag, GL_FRAGMENT_SHADER, option);
            t_vert_id = vshader.id();
            t_frag_id = fshader.id();
            t_program_id = glCreateProgram();
            t_option = option;
            linkShader();
        }

        shaderProgram::shaderProgram(const shaderProgram &s)
        {
            t_vert_id = s.t_vert_id;
            t_frag_id = s.t_frag_id;
            t_program_id = s.t_program_id;
            t_succeed = s.t_succeed;
            t_option = s.t_option;
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
                LOG_DEFAULT("error on linking shader: %s\n", infoLog);
            }
        }

        int shaderProgram::isLoaded()
        {
            return t_succeed;
        }

        void shaderProgram::use()
        {
            glUseProgram(t_program_id);
        }
    }
}

