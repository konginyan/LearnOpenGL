#include "scene.h"

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
    }
}