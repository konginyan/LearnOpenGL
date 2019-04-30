#pragma once
#include "render/transform.h"
#include "scene.h"

namespace ace
{
    namespace runtime
    {
        struct uniform
        {
            ace::render::uniformType utype;
            const float* values;
        };

        class element
        {
        protected:
            scene* t_scn;
            element* t_parent;
            std::string t_name;

        public:
            ace::render::transform t_trans; // transform
            ace::render::vertex* t_vert; // 顶点数据
            GLuint t_matl; // 材质数据
            std::string t_pass_key; // 被哪些 pass 捕捉标记

            std::vector<float> t_vertices;
            std::vector<unsigned int> t_indices;

            std::unordered_map<std::string, uniform> t_uniforms;
            std::unordered_map<std::string, element*> t_children;

        public:
            element(scene* scn, GLuint matl, std::string name);
            element(const element &elm) = delete;
            ~element();

            void addChild(element* elm) {t_children[elm->name()] = elm; elm->setParent(this);}
            void setParent(element* elm) {t_parent = elm;}
            element* getChild(std::string name) {return t_children[name];}
            element* getParent() {return t_parent;}

            void setModelUniform();
            void setUniform(std::string name, ace::render::uniformType utype, const float* val);

            inline std::string name() {return t_name;}
        };
    }
}