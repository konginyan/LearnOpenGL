#pragma once
#include "element.h"

namespace ace
{
    namespace runtime
    {
        class trangle: public element
        {
        public:
            trangle(scene* scn, ace::render::vec3 p1, ace::render::vec3 p2, ace::render::vec3 p3);
            trangle(const trangle &elm);
            ~trangle();

            void render();
        };
    }
}