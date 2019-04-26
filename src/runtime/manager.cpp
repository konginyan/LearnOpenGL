#include "manager.h"

namespace ace
{
    namespace runtime
    {
        manager::manager()
        {
        }
        
        manager::~manager()
        {
        }

        GLuint manager::genVert(int cnt, ace::render::vertexDataType* types)
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
                persize += ace::render::vertexDataSize(types[i]);
            }

            auto v = new ace::render::vertex(persize);
            v->clearBuffer();
            for(int i=0; i<cnt; i++)
            {
                v->setAttr(types[i]);
            }

            t_verts[key] = std::vector<ace::render::vertex*>();
            t_verts[key].push_back(v);
            return key;
        }

        GLuint manager::genVert(GLuint idx)
        {
            auto new_v = new ace::render::vertex(*t_verts[idx][0]);
            t_verts[idx].push_back(new_v);
            auto cnt = getVertCount(idx);
            return cnt;
        }

        ace::render::shader* manager::genShad(char* vert, char* frag)
        {
            auto shad = new ace::render::shader(vert, frag);
            auto id = shad->id();
            t_shads[id] = shad;
            return shad;
        }

        ace::render::texture* manager::genTex(char* filename)
        {
            auto tex = new ace::render::texture(filename);
            auto id = tex->id();
            t_texs[id] = tex;
            return tex;
        }

        void manager::clearVert()
        {
            for(auto &v: t_verts)
            {
                v.second[0]->clearBuffer();
            }
        }

        std::string manager::merge(material b)
        {
            material* pi = &b;
            std::string str("");
            for (int i=0; i<9; i++)
            {
                str.append(std::to_string(*((GLuint*)pi)));
                str.append("/");
                pi += sizeof(GLuint);
            }
            // str.append(std::to_string(b.shad));
            // str.append("/");
            // str.append(std::to_string(b.tex0));
            // str.append("/");
            // str.append(std::to_string(b.tex1));
            // str.append("/");
            // str.append(std::to_string(b.tex2));
            // str.append("/");
            // str.append(std::to_string(b.tex3));
            // str.append("/");
            // str.append(std::to_string(b.tex4));
            // str.append("/");
            // str.append(std::to_string(b.tex5));
            // str.append("/");
            // str.append(std::to_string(b.tex6));
            // str.append("/");
            // str.append(std::to_string(b.tex7));
            return str;
        }

        material manager::split(std::string str)
        {
            material matl;
            material* pi = &matl;
            std::string num;
            std::string::size_type pos1, pos2;

            pos2 = -1;

            for (int i=0; i<9; i++)
            {
                pos1 = pos2 + 1;
                pos2 = str.find("/", pos1);
                num = str.substr(pos1, pos2-pos1);
                *((GLuint*)pi) = atoi(num.c_str());
                pi += sizeof(GLuint);
            }

            // pos1 = 0;
            // pos2 = str.find("/");
            // num = str.substr(pos1, pos2-pos1);
            // matl.shad = atoi(num.c_str());

            // pos1 = pos2 + 1;
            // pos2 = str.find("/", pos1);
            // num = str.substr(pos1, pos2-pos1);
            // matl.tex0 = atoi(num.c_str());

            // pos1 = pos2 + 1;
            // pos2 = str.find("/", pos1);
            // num = str.substr(pos1, pos2-pos1);
            // matl.tex1 = atoi(num.c_str());

            // pos1 = pos2 + 1;
            // pos2 = str.find("/", pos1);
            // num = str.substr(pos1, pos2-pos1);
            // matl.tex2 = atoi(num.c_str());

            // pos1 = pos2 + 1;
            // pos2 = str.find("/", pos1);
            // num = str.substr(pos1, pos2-pos1);
            // matl.tex3 = atoi(num.c_str());

            // pos1 = pos2 + 1;
            // pos2 = str.find("/", pos1);
            // num = str.substr(pos1, pos2-pos1);
            // matl.tex4 = atoi(num.c_str());

            // pos1 = pos2 + 1;
            // pos2 = str.find("/", pos1);
            // num = str.substr(pos1, pos2-pos1);
            // matl.tex5 = atoi(num.c_str());

            // pos1 = pos2 + 1;
            // pos2 = str.find("/", pos1);
            // num = str.substr(pos1, pos2-pos1);
            // matl.tex6 = atoi(num.c_str());

            // pos1 = pos2 + 1;
            // pos2 = str.find("/", pos1);
            // num = str.substr(pos1, pos2-pos1);
            // matl.tex7 = atoi(num.c_str());

            return matl;
        }
    }
}