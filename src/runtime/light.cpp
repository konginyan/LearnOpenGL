#include "light.h"

namespace ace
{
    namespace runtime
    {
        light::light(scene* scn, lightType lt, ace::render::vec3 ambient, ace::render::vec3 diffuse, ace::render::vec3 specular)
            :t_type(lt),t_ambient(ambient),t_diffuse(diffuse),t_specular(specular),element(scn)
        {
            float width = 0.1f;
            float height = 0.1f;
            float length = 0.1f;

            float v[] = {
                -width/2, -height/2, -length/2, // 0
                width/2, -height/2, -length/2, // 1
                width/2, height/2, -length/2, // 2
                -width/2, height/2, -length/2, // 3
                -width/2, -height/2, length/2, // 4
                width/2, -height/2, length/2, // 5
                width/2, height/2, length/2, // 6
                -width/2, height/2, length/2 // 7
            };

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
            t_vao->setAttr(ace::render::vertexDataType::position);
            t_vao->setIndex(sizeof(idx), idx);

            t_shader = new ace::render::shaderProgram("../../shader/base.vs", "../../shader/base.fs");
        }

        light::light(const light &elm):element(elm)
        {
            t_type = elm.t_type;
            t_ambient = elm.t_ambient;
            t_diffuse = elm.t_diffuse;
            t_specular = elm.t_specular;
        }

        light::~light()
        {
        }

        void light::render()
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
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
    }
}