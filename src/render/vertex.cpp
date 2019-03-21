#include "vertex.h"

namespace ace
{
    namespace render
    {
         vertex::vertex()
         {
         }

        vertex::vertex(int per_size):t_per_size(per_size),t_attr_cnt(0),t_attr_len(0),t_buf_size(0),t_buf_capcity(0)
        {
            glGenVertexArrays(1, &t_vao);
            glGenBuffers(1, &t_vbo);
            glGenBuffers(1, &t_ebo);
        }
        
        vertex::~vertex()
        {
            glDeleteVertexArrays(1, &t_vao);
            glDeleteBuffers(1, &t_vbo);
            glDeleteBuffers(1, &t_ebo);
        }

        bool vertex::setPerSize(int size)
        {
            if(t_attr_cnt > 0)
            {
                return false;
            }
            t_per_size = size;
            return true;
        }

        void vertex::setBuffer(int size, float* vertices)
        {
            glBindVertexArray(t_vao);
            glBindBuffer(GL_ARRAY_BUFFER, t_vbo);
            glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            t_buf_capcity = size;
            t_buf_size = size;
        }

        void vertex::clearBuffer(int size)
        {
            glBindVertexArray(t_vao);
            glBindBuffer(GL_ARRAY_BUFFER, t_vbo);
            glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            t_buf_capcity = size;
            t_buf_size = 0;
        }

        void vertex::appendBuffer(int size, float* vertices)
        {
            if(t_buf_size + size > t_buf_capcity)
            {
                std::cout << "VBO Overflow!!" << std::endl;
                return;
            }
            glBindVertexArray(t_vao);
            glBindBuffer(GL_ARRAY_BUFFER, t_vbo);
            glBufferSubData(GL_ARRAY_BUFFER, t_buf_size, size, vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            t_buf_size += size;
        }

        int vertex::drawArrayCount()
        {
            return t_buf_size / t_per_size * sizeof(float);
        }

        void vertex::setIndex(int size, unsigned int* indices)
        {
            glBindVertexArray(t_vao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, t_ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        bool vertex::setAttr(vertexDataType attr_type)
        {
            int cnt = vertexDataSize(attr_type);
            if(t_attr_len + cnt > t_per_size)
            {
                std::cout << "set attribute error: vertexArray size overflow!" << std::endl;
                return false;
            }

            glBindVertexArray(t_vao);
            glBindBuffer(GL_ARRAY_BUFFER, t_vbo);
            glVertexAttribPointer(attr_type, cnt, GL_FLOAT, GL_FALSE, t_per_size * sizeof(float), (void*)(t_attr_len* sizeof(float)));
            glEnableVertexAttribArray(attr_type);
            glBindVertexArray(0);

            t_attr_cnt ++;
            t_attr_len += cnt;
            return true;
        }

        void vertex::clearAttr()
        {
            glBindVertexArray(t_vao);
            for(int i=0;i<t_attr_cnt;i++)
            {
                glDisableVertexAttribArray(t_attr_cnt);
            }
            glBindVertexArray(0);
            t_attr_cnt = 0;
            t_attr_len = 0;
        }

        bool vertex::bind()
        {
            if(t_attr_cnt > 0)
            {
                glBindVertexArray(t_vao);
                return true;
            }
            return false;
        }
    }
}