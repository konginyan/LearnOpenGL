#include "element.h"
#include "pipeline.h"

namespace ace
{
    namespace runtime
    {
        element::element(scene* scn, GLuint matl, std::string name):t_scn(scn), t_parent(nullptr),
            t_pass_key(ALL_PASS), t_matl(matl), t_name(name), t_vert(nullptr)
        {
        }

        element::~element()
        {
            delete t_vert;
            for(auto &elm: t_children)
            {
                delete elm.second;
            }
        }

        void element::setModelUniform()
        {
            const float* val = glm::value_ptr(t_trans.getModelMat());
            setUniform("model", ace::render::uniformType::mMatrix4fv, val);
        }

        void element::setUniform(std::string name, ace::render::uniformType utype, const float* val)
        {
            uniform uf = { utype, val };
            t_uniforms[name] = uf;
        }
    }
}