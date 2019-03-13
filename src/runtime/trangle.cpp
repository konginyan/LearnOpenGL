#include "trangle.h"

namespace ace
{
    namespace runtime
    {
        trangle::trangle(scene* scn, ace::render::point p1, ace::render::point p2, ace::render::point p3):element(scn)
        {
            float v[9];
            v[0] = p1.x;
            v[1] = p1.y;
            v[2] = p1.z;
            v[3] = p2.x;
            v[4] = p2.y;
            v[5] = p2.z;
            v[6] = p3.x;
            v[7] = p3.y;
            v[8] = p3.z;

            t_vao = new ace::render::vertex(3);
            t_vao->setBuffer(sizeof(v), v);
            t_vao->setAttr(3);

            t_shader = new ace::render::shaderProgram("../../shader/base.vs", "../../shader/base.fs");
        }

        trangle::trangle(const trangle &elm):element(elm)
        {
        }
        
        trangle::~trangle()
        {
            delete t_vao;
            delete t_shader;
        }

        void trangle::render()
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
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    }
}