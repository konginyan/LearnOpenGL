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
            t_bat.vert = vert;
            delete types;
        }
        
        trangle::~trangle()
        {
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