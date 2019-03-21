#include "element.h"

namespace ace
{
    namespace runtime
    {
        element::element(scene* scn):t_scn(scn)
        {
        }

        element::element(const element &elm)
        {
            t_trans = elm.t_trans;
            t_shader = elm.t_shader;
            t_scn = elm.t_scn;
            t_vao = elm.t_vao;
        }
        
        element::~element()
        {
        }

        float* element::getVertices()
        {
            if (t_bat.vert % 10 == 1)
            {
                return t_vertices;
            }
            
            auto mgr = ace::render::manager::instance();
            auto per_size = mgr->getVert(t_bat.vert)->getPerSize();
            auto pos = t_trans.getPosition();
            int v_len = t_vert_size / sizeof(float);
            for (int i=0; i< v_len; i++)
            {
                int offset = i % per_size;
                switch (offset)
                {
                case 1:
                    t_real_vertices[i] = t_vertices[i] + pos.x;
                    break;
                case 2:
                    t_real_vertices[i] = t_vertices[i] + pos.y;
                    break;
                case 3:
                    t_real_vertices[i] = t_vertices[i] + pos.z;
                    break;
                default:
                    t_real_vertices[i] = t_vertices[i];
                    break;
                }
            }
            return t_real_vertices;
        }
    }
}