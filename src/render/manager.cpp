#include "manager.h"

namespace ace
{
    namespace render
    {
        GLuint manager::base_shader_id = 0;

        manager::manager()
        {
        }
        
        manager::~manager()
        {
        }

        GLuint manager::genVert(int cnt, int* types)
        {
            int key = 0;
            for(int i=0; i<cnt; i++)
            {
                int t = types[i];
                key += 1 << t;
            }

            auto k = t_verts.find(key);
            if(k != t_verts.end())
            {
                return key;
            }

            int persize = 0;
            for(int i=0; i<cnt; i++)
            {
                persize += vertexDataSize(types[i]);
            }

            auto v = new vertex(persize);
            v->clearBuffer(max_buf_size);
            for(int i=0; i<cnt; i++)
            {
                int attr_size = vertexDataSize(types[i]);
                v->setAttr(attr_size);
            }

            t_verts[key] = v;

            return key;
        }

        void manager::clearVert()
        {
            for(auto &v: t_verts)
            {
                v.second->clearBuffer(max_buf_size);
            }
        }

        std::string manager::merge(batch b)
        {
            std::string str("");
            str.append(std::to_string(b.vert));
            str.append("/");
            str.append(std::to_string(b.shad));
            str.append("/");
            str.append(std::to_string(b.tex));
            return str;
        }

        batch manager::split(std::string str)
        {
            batch bat;
            std::string num;
            std::string::size_type pos1, pos2;

            pos1 = 0;
            pos2 = str.find("/");
            num = str.substr(pos1, pos2-pos1);
            bat.vert = atoi(num.c_str());

            pos1 = pos2 + 1;
            pos2 = str.find("/", pos1);
            num = str.substr(pos1, pos2-pos1);
            bat.shad = atoi(num.c_str());

            pos1 = pos2 + 1;
            pos2 = str.find("/", pos1);
            num = str.substr(pos1, pos2-pos1);
            bat.tex = atoi(num.c_str());

            return bat;
        }
    }
}