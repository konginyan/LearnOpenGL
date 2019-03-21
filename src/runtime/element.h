#pragma once
#include "render/transform.h"
#include "render/shader.h"
#include "render/vertex.h"
#include "scene.h"

namespace ace
{
    namespace runtime
    {
        class element
        {
        protected:
            scene* t_scn;
            ace::render::vertex* t_vao;

        public:
            ace::render::transform t_trans;
            ace::render::shaderProgram* t_shader;
            ace::render::texture* t_tex;

            float* t_vertices;
            float* t_real_vertices;
            int t_vert_size;
            ace::render::batch t_bat;

        public:
            element(scene* scn);
            element(const element &elm);
            ~element();

            float* getVertices();

            virtual void render() = 0;
        };
    }
}