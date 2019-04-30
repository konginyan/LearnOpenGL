#include "pipeline.h"
#include "interaction/log.h"

namespace ace
{
    namespace runtime
    {
        // ========= pass =============
        pass::pass(GLuint id, passType type):t_id(id), t_type(type), t_pass_filter(ALL_PASS), t_target(0)
        {
            // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
            float quad_vertices[] = {
                // positions   // texCoords
                -1.0f,  1.0f,  0.0f, 1.0f,
                -1.0f, -1.0f,  0.0f, 0.0f,
                1.0f, -1.0f,  1.0f, 0.0f,

                -1.0f,  1.0f,  0.0f, 1.0f,
                1.0f, -1.0f,  1.0f, 0.0f,
                1.0f,  1.0f,  1.0f, 1.0f
            };
            t_quad = ace::render::vertex(4);
            t_quad.setAttr(ace::render::vertexDataType::texcoord2d);
            t_quad.setAttr(ace::render::vertexDataType::texcoord2d);
            t_quad.setBuffer(sizeof(quad_vertices), quad_vertices);
        }
        
        pass::~pass()
        {
        }

        void pass::setUniform(std::string name, ace::render::uniformType utype, const float* val)
        {
            uniform uf = { utype, val };
            t_uniforms[name] = uf;
        }

        // 渲染单个 element
        void pass::renderElement(element* elm)
        {
            if (!elm->t_vert) return; // 没有顶点数据跳过

            auto res_mgr = manager::instance();

            // 使用 shader
            auto matl = res_mgr->getMaterial(elm->t_matl);

            // 如果没有shader就使用父节点的shader
            if(matl->shad == 0) {
                auto parent = elm->getParent();
                if(!parent) {
                    LOG_DEFAULT("element lack shader while render!");
                    return;
                }
                auto pmat = res_mgr->getMaterial(parent->t_matl);
                if(pmat->shad == 0) {
                    LOG_DEFAULT("element lack shader while render!");
                    return;
                }
                matl->shad = pmat->shad;
            }
            auto shad = res_mgr->getShad(matl->shad);
            shad->use();

            // 贴图
            for (unsigned int i = 0; i < 8; i++)
            {
                if (matl->tex[i] > 0)
                    res_mgr->getTex(matl->tex[i])->bind(GL_TEXTURE0 + i);
            }

            // element uniform
            for (auto &uf: elm->t_uniforms)
            {
                shad->setUniform(uf.first, uf.second.utype, uf.second.values);
            }

            // 获取光源 uniform
            for (auto &lig : t_scene->t_lights)
            {
                if(lig.second->t_pass_key != t_pass_filter) continue;
                for (auto &uf: lig.second->t_light_uniforms)
                {
                    shad->setUniform(uf.first, uf.second.utype, uf.second.values);
                }
            }

            // pass uniform
            for (auto &uf: t_uniforms)
            {
                shad->setUniform(uf.first, uf.second.utype, uf.second.values);
            }

            // model 矩阵 uniform
            elm->setModelUniform();

            // 逐个画出三角形
            auto v = elm->t_vert;
            v->bind();
            if (!elm->t_indices.empty())
            {
                glDrawElements(GL_TRIANGLES, v->drawElementCount(), GL_UNSIGNED_INT, 0);
            }
            else
            {
                glDrawArrays(GL_TRIANGLES, 0, v->drawArrayCount());
            }
        }

        // 遍历渲染所有子物体，子物体只要父物体被渲染，子物体就渲染
        void pass::renderRecursive(element* elm)
        {
            renderElement(elm);
            for(auto &e : elm->t_children)
            {
                renderRecursive(e.second);
            }
        }

        void pass::render()
        {
            if(t_type == FORWARD)
            {
                if(!t_scene) return;

                // view and projection
                auto cam = t_scene->getActiveCamera();
                auto view_mat = cam->getViewMat();
                auto proj_mat = cam->getProj();
                setUniform("view", ace::render::uniformType::mMatrix4fv, glm::value_ptr(view_mat));
                setUniform("projection", ace::render::uniformType::mMatrix4fv, glm::value_ptr(proj_mat));
                setUniform("viewPos", ace::render::uniformType::m3fv, glm::value_ptr(cam->getPosition()));

                // 遍历符合key的物体
                for (auto &e : t_scene->t_elements)
                {
                    auto elm = e.second;
                    if(elm->t_pass_key == t_pass_filter)
                        renderRecursive(elm);
                }
            }

            else if(t_type == POSTPROCESS)
            {
                auto res_mgr = manager::instance();

                // 使用 shader
                auto shad = res_mgr->getShad(t_shader);
                shad->use();

                // 贴图
                for (auto tex : t_tex_input)
                {
                    res_mgr->getTex(tex.first)->bind(GL_TEXTURE0 + tex.second);
                }

                // pass 通用 uniform
                for (auto &uf: t_uniforms)
                {
                    shad->setUniform(uf.first, uf.second.utype, uf.second.values);
                }

                // 画出矩形覆盖屏幕
                glDisable(GL_DEPTH_TEST);
                glClear(GL_COLOR_BUFFER_BIT);
                t_quad.bind();
                glDrawArrays(GL_TRIANGLES, 0, 6);
                glEnable(GL_DEPTH_TEST);
            }
        }

        // ========= pipeline =============
        pipeline::pipeline():t_pass_count(0), t_scene_count(0)
        {
        }
        
        pipeline::~pipeline()
        {
        }

        scene* pipeline::appendScene()
        {
            auto scn = new scene(t_scene_count);
            t_scenes[t_scene_count++] = scn;
            return scn;
        }

        void pipeline::setActiveScene(GLuint id)
        {
            t_active_scene = id;
        }

        pass* pipeline::genPass(passType type)
        {
            auto p = new pass(t_pass_count, type);
            t_passes[t_pass_count++] = p;
            return p;
        }

        ace::render::frame* pipeline::genFrame()
        {
            auto f = new ace::render::frame();
            t_frames[f->id()] = f;
            return f;
        }

        void pipeline::render()
        {
            GLuint mid = 0;
            for (auto &p : t_pipeline)
            {
                auto ps = getPass(p);
                ps->t_tex_input.clear();
                if(mid > 0)
                {
                    for(auto &f : getFrame(mid)->t_attaches)
                    {
                        ps->t_tex_input[f.second] = ps->t_tex_idx[f.first];
                    }
                }
                ps->t_scene = getActiveScene();
                ps->render();
                mid = ps->t_target;
            }
        }
    }
}