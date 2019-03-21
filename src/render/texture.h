#pragma once
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
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

            void bind(int idx);

            inline GLuint id() {return t_id;}
        };
    }
}