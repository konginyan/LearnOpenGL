#include "shader.h"
#include "interaction/log.h"
#include "utils/fileUtils.h"

namespace ace
{
    namespace render
    {
        shader::shader()
        {
        }

        shader::shader(char* vert, char* frag):t_linked(false)
        {
            t_vert_str = ace::utils::readFile(vert);
            t_vert_id = glCreateShader(GL_VERTEX_SHADER);
            t_frag_str = ace::utils::readFile(frag);
            t_frag_id = glCreateShader(GL_FRAGMENT_SHADER);
            t_program_id = glCreateProgram();
        }

        shader::shader(const shader &s)
        {
            t_vert_id = s.t_vert_id;
            t_frag_id = s.t_frag_id;
            t_program_id = s.t_program_id;
            t_linked = s.t_linked;
        }

        shader::~shader()
        {
            glDeleteShader(t_vert_id);
            glDeleteShader(t_frag_id);
            glDeleteProgram(t_program_id);
        }

        void shader::setMarco(char* marco)
        {
            if(t_linked) {
                LOG_DEFAULT("error on set shader marco: cannot set marco on a linked shader!");
                return;
            }

            auto def = std::string("#define ");

            int first_line_end = t_vert_str.find_first_of("\n");
            t_vert_str.insert(first_line_end + 1, def + marco + "\n");

            first_line_end = t_frag_str.find_first_of("\n");
            t_frag_str.insert(first_line_end + 1, def + marco + "\n");
        }

        void shader::compileAndLink()
        {
            const char* v_src_str = t_vert_str.c_str();
            glShaderSource(t_vert_id, 1, &v_src_str, NULL);

            const char* f_src_str = t_frag_str.c_str();
            glShaderSource(t_frag_id, 1, &f_src_str, NULL);

            glCompileShader(t_vert_id);

            char infoLog[512];
            int flag;
            glGetShaderiv(t_vert_id, GL_COMPILE_STATUS, &flag);
            if(!flag)
            {
                glGetShaderInfoLog(t_vert_id, 512, NULL, infoLog);
                LOG_DEFAULT("error on loading shader: %s\n", infoLog);
                return;
            }

            glCompileShader(t_frag_id);

            glGetShaderiv(t_frag_id, GL_COMPILE_STATUS, &flag);
            if(!flag)
            {
                glGetShaderInfoLog(t_frag_id, 512, NULL, infoLog);
                LOG_DEFAULT("error on loading shader: %s\n", infoLog);
                return;
            }

            glAttachShader(t_program_id, t_vert_id);
            glAttachShader(t_program_id, t_frag_id);
            glLinkProgram(t_program_id);

            glGetProgramiv(t_program_id, GL_LINK_STATUS, &flag);
            if(!flag) {
                glGetProgramInfoLog(t_program_id, 512, NULL, infoLog);
                LOG_DEFAULT("error on linking shader: %s\n", infoLog);
                return;
            }

            t_linked = true;
        }

        void shader::use()
        {
            if(!t_linked) {
                LOG_DEFAULT("error on use shader: the shader should be linked first!");
                return;
            }
            glUseProgram(t_program_id);
        }
    }
}

