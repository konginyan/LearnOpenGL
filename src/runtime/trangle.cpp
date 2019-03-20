#include "trangle.h"

namespace ace
{
    namespace runtime
    {
        trangle::trangle(scene* scn, ace::render::vec3 p1, ace::render::vec3 p2, ace::render::vec3 p3):element(scn)
        {
            t_vertices = new float[9]{
                p1.x, p1.y, p1.z,
                p2.x, p2.y, p2.z,
                p3.x, p3.y, p3.z
            };

            t_vert_size = 9 * sizeof(float);
            auto mgr = ace::render::manager::instance();
            auto types = new int[1]{ace::render::vertexDataType::position};
            GLuint vert = mgr->genVert(1, types);
            delete types;

            t_bat = {vert, mgr->base_shader_id, 0};

            // float v[] = {
            //     p1.x, p1.y, p1.z,
            //     p2.x, p2.y, p2.z,
            //     p3.x, p3.y, p3.z
            // };

            // t_vao = new ace::render::vertex(3);
            // t_vao->setBuffer(sizeof(v), v);
            // t_vao->setAttr(3);

            // t_shader = new ace::render::shaderProgram("../../../shader/white.vs", "../../../shader/white.fs");
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
            t_vao->bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    }
}