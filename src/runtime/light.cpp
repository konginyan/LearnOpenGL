#include "light.h"

namespace ace
{
    namespace runtime
    {
        light::light(scene* scn, lightType lt):t_type(lt),element(scn)
        {
            float width = 0.1f;
            float height = 0.1f;
            float length = 0.1f;

            int vsize = 24;
            int isize = 36;

            t_vertices = new float[vsize]{
                -width/2, -height/2, -length/2, // 0
                width/2, -height/2, -length/2, // 1
                width/2, height/2, -length/2, // 2
                -width/2, height/2, -length/2, // 3
                -width/2, -height/2, length/2, // 4
                width/2, -height/2, length/2, // 5
                width/2, height/2, length/2, // 6
                -width/2, height/2, length/2 // 7
            };

            t_indices = new int[isize]{
                0, 1, 3,
                3, 2, 1,
                4, 5, 7,
                7, 6, 5,
                0, 3, 4,
                3, 7, 4,
                1, 2, 5,
                2, 6, 5,
                3, 7, 2,
                7, 6, 2,
                0, 4, 1,
                4, 5, 1
            };

            t_real_vertices = new float[vsize];

            t_vert_size = vsize * sizeof(float);
            t_idx_size = isize * sizeof(int);
            auto mgr = ace::render::manager::instance();
            auto types = new ace::render::vertexDataType[2]{
                ace::render::vertexDataType::position
            };
            GLuint vert = mgr->genVert(1, types);
            t_bat.vert = vert;
            delete types;
        }

        light::~light()
        {
        }

        void light::setLightUniform(char* name, ace::render::uniformType utype, const float* val)
        {
            uniform uf = { utype, val };
            t_light_uniforms[name] = uf;
        }

        void light::update()
        {

        }

        void light::render()
        {

        }
    }
}