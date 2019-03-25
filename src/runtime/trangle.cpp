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

            t_bat = {vert, 0, 0, mgr->base_shader_id, mgr->base_texture_id};
        }

        trangle::trangle(const trangle &elm):element(elm)
        {
        }
        
        trangle::~trangle()
        {
            delete t_vao;
            delete t_shader;
        }

        void trangle::update()
        {
            auto mgr = ace::render::manager::instance();
            auto v = mgr->getVert(t_bat.vert, t_bat.vert_part);
            v->modifyBuffer(t_bat.vert_start, t_vert_size, getVertices());
        }

        void trangle::render()
        {
        }
    }
}