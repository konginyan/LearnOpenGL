#include "element.h"

namespace ace
{
    namespace runtime
    {
        enum lightType {DIERCT, POINT, SPOT};

        class light: public element
        {
        public:
            ace::render::vec3 t_ambient;
            ace::render::vec3 t_diffuse;
            ace::render::vec3 t_specular;
            lightType t_type;

        public:
            light(scene* scn, lightType lt, ace::render::vec3 ambient, ace::render::vec3 diffuse, ace::render::vec3 specular);
            light(const light &elm);
            ~light();

            void render();
        };
    }
}