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
            ace::render::batch t_bat;

            float* t_vertices;
            float* t_real_vertices;
            int t_vert_size;
            int* t_indices;
            int t_idx_size;

            std::unordered_map<char*, uniform> t_uniforms;

        public:
            element(scene* scn);
            element(const element &elm) = delete;
            ~element();

            void setUniform(char* name, ace::render::uniformType utype, const float* val);
            float* getVertices();

            virtual void update() = 0;
            virtual void render() = 0;
        };
    }
}