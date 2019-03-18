#include "trangle.h"

namespace ace
{
    namespace runtime
    {
        trangle::trangle(scene* scn, ace::render::vec3 p1, ace::render::vec3 p2, ace::render::vec3 p3):element(scn)
        {
            float v[9] = {
                p1.x, p1.y, p1.z,
                p2.x, p2.y, p2.z,
                p3.x, p3.y, p3.z
            };

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

            t_shader->setUniformMatrix4fv("model", glm::value_ptr(model_mat));
            t_shader->setUniformMatrix4fv("view", glm::value_ptr(view_mat));
            t_shader->setUniformMatrix4fv("projection", glm::value_ptr(proj_mat));

            t_vao->bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    }
}