#pragma once
#include "element.h"

namespace ace
{
    namespace runtime
    {
        class cube: public element
        {
        public:
            cube(scene* scn, GLuint matl);
            cube(const cube &elm) = delete;
            ~cube();
        };
    }
}