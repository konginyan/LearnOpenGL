#pragma once
#include "scene.h"

namespace ace
{
    namespace runtime
    {
        class cube: public element
        {
        public:
            cube(scene* scn, float length, float width, float height);
            cube(const cube &elm);
            ~cube();

            void render();
        };
    }
}