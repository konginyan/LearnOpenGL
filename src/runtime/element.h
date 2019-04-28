#pragma once
#include <unordered_map>
#include "render/transform.h"
#include "render/shader.h"
#include "render/vertex.h"
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

        public:
            ace::render::transform t_trans;
            ace::render::vertex* t_vert;
            GLuint t_matl;
            std::string t_pass_key;

            float* t_vertices;
            int t_vert_size;
            int* t_indices;
            int t_idx_size;

            std::unordered_map<char*, uniform> t_uniforms;

        public:
            element(scene* scn, GLuint matl);
            element(const element &elm) = delete;
            ~element();

            void setModelUniform();
            void setUniform(char* name, ace::render::uniformType utype, const float* val);
        };
    }
}