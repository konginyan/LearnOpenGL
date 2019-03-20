#pragma once
#include "stb/stb_image.h"
#include "glSupport.h"

namespace ace
{
    namespace render
    {
        class texture
        {
        private:
            GLuint t_id;
        public:
            texture(char* filename);
            texture(const texture &tex);
            ~texture();

            inline GLuint id() {return t_id;}
        };
    }
}