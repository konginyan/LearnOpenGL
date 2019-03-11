#pragma once
#include "glSupport.h"

namespace ace
{
    namespace render
    {
        struct point
        {
            float x, y, z;
        };
        
        class vertex
        {
        private:
            int t_per_size;
            int t_attr_cnt;
            int t_attr_len;
            GLuint t_vao;
            GLuint t_vbo;
            GLuint t_ebo;

        public:
            vertex();
            vertex(int per_size);
            vertex(const vertex &v) = delete;
            ~vertex();

            bool setSize(int size);
            void setBuffer(int size, float* vertices);
            void setIndex(int size, unsigned int* indices);
            bool setAttr(int cnt);
            void bind();
        };
    }// render
}// ace