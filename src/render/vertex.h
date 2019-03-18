#pragma once
#include "glSupport.h"

namespace ace
{
    namespace render
    {
        struct vec3
        {
            float x, y, z;
        };

        static float* vec2array(vec3 v)
        {
            float* f = new float[3]{v.x, v.y, v.z};
            return f;
        }
        
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
            void clearAttr();
            bool bind();
        };
    }// render
}// ace