#include "light.h"
#include "pipeline.h"

namespace ace
{
    namespace runtime
    {
        light::light(scene* scn, lightType lt):t_type(lt),t_pass_key(ALL_PASS)
        {
        }

        light::~light()
        {
        }

        void light::setLightUniform(std::string name, ace::render::uniformType utype, const float* val)
        {
            uniform uf = { utype, val };
            t_light_uniforms[name] = uf;
        }
    }
}