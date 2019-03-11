#pragma once
#include "scene.h"

namespace ace
{
    namespace runtime
    {
        class trangle: public element
        {
        public:
            trangle(scene* scn, ace::render::point p1, ace::render::point p2, ace::render::point p3);
            trangle(const trangle &t);
            ~trangle();

            void render();
        };
    }
}