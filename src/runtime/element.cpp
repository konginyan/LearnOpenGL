#include "element.h"
#include "pipeline.h"

namespace ace
{
    namespace runtime
    {
        element::element(scene* scn, GLuint matl):t_scn(scn), t_vert_size(0), t_idx_size(0), t_pass_key(ALL_PASS), t_matl(matl)
        {
        }

        element::~element()
        {
            delete t_vert;
            delete t_vertices;
            delete t_indices;
        }

        void element::setModelUniform()
        {
            const float* val = glm::value_ptr(t_trans.getModelMat());
            setUniform("model", ace::render::uniformType::mMatrix4fv, val);
        }

        void element::setUniform(char* name, ace::render::uniformType utype, const float* val)
        {
            uniform uf = { utype, val };
            t_uniforms[name] = uf;
        }
    }
}