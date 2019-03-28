#include "element.h"

namespace ace
{
    namespace runtime
    {
        element::element(scene* scn):t_scn(scn), t_vert_size(0), t_idx_size(0),t_bat({0,0,0,0,0})
        {
        }
        
        element::~element()
        {
            delete t_vertices;
            delete t_real_vertices;
            delete t_indices;
        }

        void element::setUniform(char* name, ace::render::uniformType utype, const float* val)
        {
            uniform uf = { utype, val };
            t_uniforms[name] = uf;
        }

        float* element::getVertices()
        {
            if (t_bat.vert % 2 != 1)
            {
                return t_vertices;
            }
            
            auto mgr = ace::render::manager::instance();
            auto per_size = mgr->getVert(t_bat.vert, t_bat.vert_part)->getPerSize();
            auto pos = t_trans.getPosition();
            int v_len = t_vert_size / sizeof(float);
            for (int i=0; i< v_len; i++)
            {
                int offset = i % per_size;
                switch (offset)
                {
                case 0:
                    t_real_vertices[i] = t_vertices[i] + pos.x;
                    break;
                case 1:
                    t_real_vertices[i] = t_vertices[i] + pos.y;
                    break;
                case 2:
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