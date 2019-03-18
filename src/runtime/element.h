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

        public:
            element(scene* scn);
            element(const element &elm);
            ~element();

            virtual void render() = 0;
        };
    }
}