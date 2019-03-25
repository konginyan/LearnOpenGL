#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "vertex.h"
#include "shader.h"
#include "texture.h"

namespace ace
{
    namespace render
    {
        struct batch
        {
            GLuint vert;
            GLuint vert_part;
            GLuint vert_start;
            GLuint shad;
            GLuint tex;
        };

        class manager
        {
        private:
            std::unordered_map<GLuint, std::vector<vertex*>> t_verts;
            std::unordered_map<GLuint, shaderProgram*> t_shads;
            std::unordered_map<GLuint, texture*> t_texs;

        public:
            static GLuint base_shader_id;
            static GLuint base_texture_id;

            static manager* instance() 
            {
                static manager t_ins;
                return &t_ins;
            }

        public:
            manager();
            ~manager();

            GLuint genVert(int cnt, vertexDataType* types);
            GLuint genVert(GLuint idx);
            GLuint genShad(shaderProgram* s) { t_shads[s->id()] = s; return s->id(); }
            GLuint genTex(texture* tex) { t_texs[tex->id()] = tex; return tex->id(); }
            vertex* getVert(GLuint idx, GLuint part) {return t_verts[idx][part];}
            int getVertCount(GLuint idx) { return t_verts[idx].size() - 1; }
            shaderProgram* getShad(GLuint idx) {return t_shads[idx];}
            texture* getTex(GLuint idx) {return t_texs[idx];}

            void clearVert();

            std::string merge(batch b);
            batch split(std::string str);
        };
    }
}