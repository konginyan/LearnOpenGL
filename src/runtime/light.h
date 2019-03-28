#include <unordered_map>
#include "element.h"

namespace ace
{
    namespace runtime
    {
        enum lightType {DIRECT, POINT, SPOT};

        class light: public element
        {
        public:
            std::unordered_map<char*, uniform> t_light_uniforms;
            lightType t_type;

        public:
            light(scene* scn, lightType lt);
            light(const light &elm) = delete;
            ~light();

            void setLightUniform(char* name, ace::render::uniformType utype, const float* val);

            void update();
            void render();
        };
    }
}