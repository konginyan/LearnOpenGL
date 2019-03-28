#include "cube.h"
#include "light.h"

namespace ace
{
    namespace runtime
    {
        cube::cube(scene* scn, float length, float width, float height):element(scn)
        {
            int vsize = 24 * 8;
            int isize = 36;
            t_vertices = new float[vsize]{
                // position                         // normal               // texcoord

                // point 0
                -width/2, -height/2, -length/2,    -1.0f, 0.0f, 0.0f,       1.0f, 0.0f,   // 0
                -width/2, -height/2, -length/2,     0.0f, -1.0f, 0.0f,      0.0f, 0.0f,   // 1
                -width/2, -height/2, -length/2,     0.0f, 0.0f, -1.0f,      0.0f, 0.0f,   // 2

                // point 1
                width/2, -height/2, -length/2,     1.0f, 0.0f, 0.0f,        0.0f, 0.0f,   // 3
                width/2, -height/2, -length/2,     0.0f, -1.0f, 0.0f,       1.0f, 0.0f,   // 4
                width/2, -height/2, -length/2,     0.0f, 0.0f, -1.0f,       1.0f, 0.0f,   // 5

                // point 2
                width/2, height/2, -length/2,     1.0f, 0.0f, 0.0f,         0.0f, 1.0f,   // 6
                width/2, height/2, -length/2,     0.0f, 1.0f, 0.0f,         1.0f, 0.0f,   // 7
                width/2, height/2, -length/2,     0.0f, 0.0f, -1.0f,        1.0f, 1.0f,   // 8

                // point 3
                -width/2, height/2, -length/2,     -1.0f, 0.0f, 0.0f,       1.0f, 1.0f,   // 9
                -width/2, height/2, -length/2,     0.0f, 1.0f, 0.0f,        0.0f, 0.0f,   // 10
                -width/2, height/2, -length/2,     0.0f, 0.0f, -1.0f,       0.0f, 1.0f,   // 11

                // point 4
                -width/2, -height/2, length/2,     -1.0f, 0.0f, 0.0f,       0.0f, 0.0f,   // 12
                -width/2, -height/2, length/2,     0.0f, -1.0f, 0.0f,       0.0f, 1.0f,   // 13
                -width/2, -height/2, length/2,     0.0f, 0.0f, 1.0f,        0.0f, 0.0f,   // 14

                // point 5
                width/2, -height/2, length/2,     1.0f, 0.0f, 0.0f,         1.0f, 0.0f,   // 15
                width/2, -height/2, length/2,     0.0f, -1.0f, 0.0f,        1.0f, 1.0f,   // 16
                width/2, -height/2, length/2,     0.0f, 0.0f, 1.0f,         1.0f, 0.0f,   // 17

                // point 6
                width/2, height/2, length/2,     1.0f, 0.0f, 0.0f,          1.0f, 1.0f,   // 18
                width/2, height/2, length/2,     0.0f, 1.0f, 0.0f,          1.0f, 1.0f,   // 19
                width/2, height/2, length/2,     0.0f, 0.0f, 1.0f,          1.0f, 1.0f,   // 20

                // point 7
                -width/2, height/2, length/2,     -1.0f, 0.0f, 0.0f,        0.0f, 1.0f,   // 21
                -width/2, height/2, length/2,     0.0f, 1.0f, 0.0f,         0.0f, 1.0f,   // 22
                -width/2, height/2, length/2,     0.0f, 0.0f, 1.0f,         0.0f, 1.0f,   // 23
            };

            t_indices = new int[isize]{
                2, 5, 11,
                11, 8, 5,
                14, 17, 23,
                23, 20, 17,
                0, 9, 12,
                9, 12, 21,
                3, 6, 15,
                6, 18, 15,
                10, 22, 7,
                22, 19, 7,
                1, 13, 4,
                13, 16, 4
            };

            t_real_vertices = new float[vsize];

            t_vert_size = vsize * sizeof(float);
            t_idx_size = isize * sizeof(int);
            auto mgr = ace::render::manager::instance();
            auto types = new ace::render::vertexDataType[3]{
                ace::render::vertexDataType::position,
                ace::render::vertexDataType::normal,
                ace::render::vertexDataType::texcoord2d
            };
            GLuint vert = mgr->genVert(3, types);
            t_bat.vert = vert;
            delete types;
        }
        
        cube::~cube()
        {
        }

        void cube::update()
        {

        }

        void cube::render()
        {
            //t_shader->use();

            //auto model_mat = t_trans.getTransform();
            //auto active_camera = t_scn->getActiveCamera();
            //auto view_mat = active_camera->getViewMat();
            //auto proj_mat = active_camera->getProj();

            //t_shader->setUniformMatrix4fv("model", glm::value_ptr(model_mat));
            //t_shader->setUniformMatrix4fv("view", glm::value_ptr(view_mat));
            //t_shader->setUniformMatrix4fv("projection", glm::value_ptr(proj_mat));
            //t_shader->setUniform3fv("viewPos", glm::value_ptr(active_camera->t_trans.getPosition()));

            //float amb[] = { 1.0f, 0.5f, 0.31f };
            //float dif[] = { 1.0f, 0.5f, 0.31f };
            //float spc[] = { 0.5f, 0.5f, 0.5f };
            //t_shader->setUniform3fv("material.ambient", amb);
            //t_shader->setUniform3fv("material.diffuse", dif);
            //t_shader->setUniform3fv("material.specular", spc);
            //t_shader->setUniform1f("material.shininess", 32.0f);

            //t_vao->bind();

            //for (auto it = t_scn->t_lights.begin(); it != t_scn->t_lights.end(); it++)
            //{
            //    auto lig = it->second;
            //    t_shader->setUniform3fv("light.position", glm::value_ptr(lig->t_trans.getPosition()));
            //    t_shader->setUniform3fv("light.ambient", ace::render::vec2array(lig->t_ambient));
            //    t_shader->setUniform3fv("light.diffuse", ace::render::vec2array(lig->t_diffuse));
            //    t_shader->setUniform3fv("light.specular", ace::render::vec2array(lig->t_specular));

            //    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //}
        }
    }
}