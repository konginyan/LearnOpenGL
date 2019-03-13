#include "cube.h"

namespace ace
{
    namespace runtime
    {
        cube::cube(scene* scn, float length, float width, float height):element(scn)
        {
            float v[24];
            //0
            v[0] = -width/2;
            v[1] = -height/2;
            v[2] = -length/2;
            //1
            v[3] = width/2;
            v[4] = -height/2;
            v[5] = -length/2;
            //2
            v[6] = width/2;
            v[7] = height/2;
            v[8] = -length/2;
            //3
            v[9] = -width/2;
            v[10] = height/2;
            v[11] = -length/2;
            //4
            v[12] = -width/2;
            v[13] = -height/2;
            v[14] = length/2;
            //5
            v[15] = width/2;
            v[16] = -height/2;
            v[17] = length/2;
            //6
            v[18] = width/2;
            v[19] = height/2;
            v[20] = length/2;
            //7
            v[21] = -width/2;
            v[22] = height/2;
            v[23] = length/2;

            GLuint idx[] = {
                0, 1, 3,
                3, 2, 1,
                4, 5, 7,
                7, 6, 5,
                0, 3, 4,
                3, 7, 4,
                1, 2, 5,
                2, 6, 5,
                3, 7, 2,
                7, 6, 2,
                0, 4, 1,
                4, 5, 1
            };

            t_vao = new ace::render::vertex(3);
            t_vao->setBuffer(sizeof(v), v);
            t_vao->setAttr(3);
            t_vao->setIndex(sizeof(idx), idx);

            t_shader = new ace::render::shaderProgram("../../shader/base.vs", "../../shader/base.fs");
        }

        cube::cube(const cube &elm):element(elm)
        {
        }
        
        cube::~cube()
        {
        }

        void cube::render()
        {
            t_shader->use();

            auto model_mat = t_trans.getTransform();
            auto active_camera = t_scn->getActiveCamera();
            auto view_mat = active_camera->getViewMat();
            auto proj_mat = active_camera->getProj();

            t_shader->setUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(model_mat));
            t_shader->setUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(view_mat));
            t_shader->setUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(proj_mat));

            t_vao->bind();
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
    }
}