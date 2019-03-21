#include "trangle.h"

namespace ace
{
    namespace runtime
    {
        trangle::trangle(scene* scn, ace::render::vec3 p1, ace::render::vec3 p2, ace::render::vec3 p3):element(scn)
        {
            t_vertices = new float[15]{
                p1.x, p1.y, p1.z, 0.5f, 1.0f,
                p2.x, p2.y, p2.z, 0.0f, 0.0f,
                p3.x, p3.y, p3.z, 1.0f, 0.0f
            };

            t_real_vertices = new float[15];

            t_vert_size = 15 * sizeof(float);
            auto mgr = ace::render::manager::instance();
            auto types = new ace::render::vertexDataType[2]{
                ace::render::vertexDataType::position,
                ace::render::vertexDataType::texcoord2d
            };
            GLuint vert = mgr->genVert(2, types);
            delete types;

            t_bat = {vert, mgr->base_shader_id, mgr->base_texture_id};

            ////////////////////////////////////////////////////
            //float v[] = {
            //    p1.x, p1.y, p1.z, 0.5f, 1.0f,
            //    p2.x, p2.y, p2.z, 0.0f, 0.0f,
            //    p3.x, p3.y, p3.z, 1.0f, 0.0f
            //};

            //t_vao = new ace::render::vertex(5);
            //t_vao->setBuffer(sizeof(v), v);
            //t_vao->setAttr(ace::render::vertexDataType::position);
            //t_vao->setAttr(ace::render::vertexDataType::texcoord2d);
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
            auto mgr = ace::render::manager::instance();
            mgr->getTex(t_bat.tex)->bind(GL_TEXTURE0);
            mgr->getShad(t_bat.shad)->use();
            t_vao->bind();
            glDrawArrays(GL_TRIANGLES, 0, 15);
        }
    }
}