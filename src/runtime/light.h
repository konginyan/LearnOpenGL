#pragma once
#include <unordered_map>
#include "element.h"

namespace ace
{
    namespace runtime
    {
        enum lightType {DIRECT, POINT, SPOT};

        class light
        {
        public:
            ace::render::transform t_trans;
            std::unordered_map<std::string, uniform> t_light_uniforms;
            lightType t_type;
            std::string t_pass_key;

        public:
            light(scene* scn, lightType lt);
            light(const light &elm) = delete;
            ~light();

            void setLightUniform(std::string name, ace::render::uniformType utype, const float* val);
        };
    }
}