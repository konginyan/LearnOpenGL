#pragma once
#include <vector>
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

        static float* float2array(float f1)
        {
            float* f = new float[1]{ f1 };
            return f;
        }

        static float* float2array(float f1, float f2, float f3)
        {
            float* f = new float[3]{ f1,f2,f3 };
            return f;
        }

        enum vertexDataType {position, normal, texcoord2d};

        static int vertexDataSize(vertexDataType option)
        {
            switch (option)
            {
                case position:
                    return 3;

                case normal:
                    return 3;

                case texcoord2d:
                    return 2;

                default:
                    return 0;
            }
        }
        
        class vertex
        {
        private:
            std::vector<vertexDataType> t_attr_cnt;
            int t_per_size;
            int t_attr_len;
            int t_buf_size;
            int t_buf_capcity;
            int t_idx_size;
            GLuint t_vao;
            GLuint t_vbo;
            GLuint t_ebo;

        public:
            static const int MAX_BUF_SIZE = 1024 * 15 * sizeof(float);

        public:
            vertex();
            vertex(int per_size);
            vertex(const vertex &v);
            ~vertex();

            int getPerSize() { return t_per_size; }
            bool setPerSize(int size); // 设置单个点大小
            void setBuffer(int size, float* vertices); // 重新设置静态 buffer
            void clearBuffer(int size = MAX_BUF_SIZE); // 清除 buffer，生成固定大小的动态空 buffer
            int appendBuffer(int size, float* vertices); // 向动态 buffer 添加数据
            void modifyBuffer(int offset, int size, float* vertices); // 修改 buffer 中被定义过的数据
            int drawArrayCount(); // 获取 drawArray 方法的顶点数
            int drawElementCount(); // 获取 drawElement 方法的顶点数

            void setIndex(int size, int* indices); // 设置索引
            bool setAttr(vertexDataType attr_type); // 添加并设置属性大小
            void clearAttr(); // 删除所有属性
            bool bind(); // 绑定 vao

            inline GLuint id() {return t_vao;}
        };
    }
}