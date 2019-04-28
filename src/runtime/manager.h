#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "render/vertex.h"
#include "render/shader.h"
#include "render/texture.h"

namespace ace
{
    namespace runtime
    {
        struct material
        {
            GLuint id;
            GLuint shad;
            GLuint tex0;
            GLuint tex1;
            GLuint tex2;
            GLuint tex3;
            GLuint tex4;
            GLuint tex5;
            GLuint tex6;
            GLuint tex7;
        };

        struct batch
        {
            GLuint id;
            GLuint vert;
            material matl;
        };
        

        class manager
        {
        private:
            int t_matl_cnt;
            int t_bat_cnt;

        public:
            std::unordered_map<GLuint, std::vector<ace::render::vertex*>> t_verts;
            std::unordered_map<GLuint, ace::render::shader*> t_shads;
            std::unordered_map<GLuint, ace::render::texture*> t_texs;
            std::unordered_map<GLuint, material*> t_matls;
            std::unordered_map<GLuint, batch*> t_bats;

        public:
            static manager* instance()
            {
                static manager t_ins;
                return &t_ins;
            }

        public:
            manager();
            ~manager();

            GLuint genVert(int cnt, ace::render::vertexDataType* types);
            GLuint genVert(GLuint idx);
            ace::render::shader* genShad(char* vert, char* frag);
            ace::render::texture* genTex(char* filename);
            material* genMaterial();
            ace::render::vertex* getVert(GLuint idx, GLuint part) {return t_verts[idx][part];}
            int getVertCount(GLuint idx) { return t_verts[idx].size() - 1; }
            ace::render::shader* getShad(GLuint idx) {return t_shads[idx];}
            ace::render::texture* getTex(GLuint idx) {return t_texs[idx];}
            material* getMaterial(GLuint idx) {return t_matls[idx];}

            void clearVert();

            std::string merge(material b);
            material split(std::string str);
        };
    }
}