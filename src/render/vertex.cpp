#include "vertex.h"

namespace ace
{
    namespace render
    {
         vertex::vertex()
         {
         }

        vertex::vertex(int per_size):t_per_size(per_size),t_attr_cnt(0),t_attr_len(0)
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

        bool vertex::setSize(int size)
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
        }

        void vertex::setIndex(int size, unsigned int* indices)
        {
            glBindVertexArray(t_vao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, t_ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        bool vertex::setAttr(int cnt)
        {
            if(t_attr_len + cnt > t_per_size)
            {
                std::cout << "set attribute error: vertexArray size overflow!" << std::endl;
                return false;
            }

            glBindVertexArray(t_vao);
            glBindBuffer(GL_ARRAY_BUFFER, t_vbo);
            glVertexAttribPointer(t_attr_cnt, cnt, GL_FLOAT, GL_FALSE, t_per_size * sizeof(float), (void*)(t_attr_len* sizeof(float)));
            glEnableVertexAttribArray(0);
            glBindVertexArray(0);

            t_attr_cnt ++;
            t_attr_len += cnt;
            return true;
        }

        void vertex::bind()
        {
            glBindVertexArray(t_vao);
        }
    }// render
}// ace