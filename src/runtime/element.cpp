#include "element.h"
#include "pipeline.h"

namespace ace
{
    namespace runtime
    {
        element::element(scene* scn):t_scn(scn), t_vert_size(0), t_idx_size(0), t_pass_key(ALL_PASS)
        {
        }

        element::~element()
        {
            delete t_vertices;
            delete t_indices;
        }

        void element::setUniform(char* name, ace::render::uniformType utype, const float* val)
        {
            uniform uf = { utype, val };
            t_uniforms[name] = uf;
        }
    }
}