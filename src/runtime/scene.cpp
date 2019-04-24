#include "element.h"
#include "light.h"

namespace ace
{
    namespace runtime
    {
        scene::scene():t_render(this)
        {
            auto cam = new ace::runtime::camera();
            cam->setPersProj(45.0f, 800.0f, 600.0f, 0.1f, 100.0f);
            cam->move(-3.0f, 0.0f);
            t_cameras["main"] = cam;
            setActiveCamera("main");
        }

        scene::~scene()
        {
            for(auto &elm: t_elements)
            {
                delete elm.second;
            }

            for(auto &cam: t_cameras)
            {
                delete cam.second;
            }

            for(auto &lig: t_lights)
            {
                delete lig.second;
            }
        }

        void scene::addElement(std::string name, element* elm)
        {
            t_elements[name] = elm;
        }

        camera* scene::addCamera(std::string name)
        {
            auto cam = new camera();
            t_cameras[name] = cam;
            return cam;
        }

        light* scene::addLight(std::string name, lightType lt)
        {
            auto lig = new light(this, lt);
            t_lights[name] = lig;
            t_elements[name] = lig;
            return lig;
        }

        void scene::setActiveCamera(std::string name)
        {
            t_active_camera = name;
        }

        camera* scene::getActiveCamera()
        {
            return t_cameras[t_active_camera];
        }

        element* scene::operator[](std::string name)
        {
            return t_elements[name];
        }

        void scene::update()
        {
            for (auto &e : t_elements)
            {
                auto elm = e.second;
                elm->update();
            }
        }

        void scene::render()
        {
            t_render.onRenderBegin();
            t_render.render();
            t_render.onRenderEnd();
        }

        // ============= renderer ===================
        renderer::renderer(scene* scn):t_isbatch(false),t_scn(scn),t_drawcall(0)
        {
        }
        
        renderer::~renderer()
        {
        }

        void renderer::makeBatch()
        {
            if (!t_isbatch)
                return;

            auto mgr = ace::render::manager::instance();
            mgr->clearVert();
            t_batches.clear();
            for (auto &e : t_scn->t_elements)
            {
                auto elm = e.second;
                int v_cnt = mgr->getVertCount(elm->t_bat.vert);
                auto v = mgr->getVert(elm->t_bat.vert, v_cnt);
                int start_size = v->appendBuffer(elm->t_vert_size, elm->t_vertices);

                if (start_size == -1)
                {
                    v_cnt = mgr->genVert(elm->t_bat.vert);
                    v = mgr->getVert(elm->t_bat.vert, v_cnt);
                    v->appendBuffer(elm->t_vert_size, elm->t_vertices);
                    elm->t_bat.vert_part = v_cnt;
                    elm->t_bat.vert_start = 0;
                }
                else
                {
                    elm->t_bat.vert_part = v_cnt;
                    elm->t_bat.vert_start = start_size;
                }

                auto batch_code = mgr->merge(elm->t_bat);
                auto b = t_batches.find(batch_code);
                if (b == t_batches.end())
                {
                    t_batches[batch_code] = 0;
                }
                else
                {
                    t_batches[batch_code] = v_cnt;
                }
            }
        }

        void renderer::onRenderBegin()
        {
            t_drawcall = 0;

            auto mgr = ace::render::manager::instance();
            for (auto &shad_pair : mgr->t_shads)
            {
                auto shad = shad_pair.second;
                shad->use();
                auto active_camera = t_scn->getActiveCamera();
                auto view_mat = active_camera->getViewMat();
                auto proj_mat = active_camera->getProj();

                shad->setUniformMatrix4fv("view", glm::value_ptr(view_mat));
                shad->setUniformMatrix4fv("projection", glm::value_ptr(proj_mat));
            }
        }

        void renderer::render()
        {
            auto mgr = ace::render::manager::instance();
            if(t_isbatch)
            {
                for (auto &bat : t_batches)
                {
                    for (int i = 0; i <= bat.second; i++)
                    {
                        ace::render::batch b = mgr->split(bat.first);
                        mgr->getShad(b.shad)->use();
                        auto v = mgr->getVert(b.vert, i);
                        v->bind();
                        glDrawArrays(GL_TRIANGLES, 0, v->drawArrayCount());
                        t_drawcall++;
                    }
                }
            }
            else
            {
                for (auto &e : t_scn->t_elements)
                {
                    auto elm = e.second;
                    ace::render::batch b = elm->t_bat;

                    auto shad = mgr->getShad(b.shad);
                    shad->use();

                    // ���� shader ����
                    if (shad->t_option.LIGHT)
                    {
                        shad->setUniform("viewPos", ace::render::m3fv, glm::value_ptr(t_scn->getActiveCamera()->getPosition()));
                        for (auto &lig : t_scn->t_lights)
                        {
                            for (auto &uf: lig.second->t_light_uniforms)
                            {
                                shad->setUniform(uf.first, uf.second.utype, uf.second.values);
                            }
                        }
                    }

                    // ���� shader ����
                    for (auto &uf : elm->t_uniforms)
                    {
                        shad->setUniform(uf.first, uf.second.utype, uf.second.values);
                    }

                    auto v = mgr->getVert(b.vert, b.vert_part);
                    v->setBuffer(elm->t_vert_size, elm->getVertices());
                    if (elm->t_idx_size > 0)
                    {
                        v->setIndex(elm->t_idx_size, elm->t_indices);
                        v->bind();
                        glDrawElements(GL_TRIANGLES, v->drawElementCount(), GL_UNSIGNED_INT, 0);
                    }
                    else
                    {
                        v->bind();
                        glDrawArrays(GL_TRIANGLES, 0, v->drawArrayCount());
                    }
                    t_drawcall++;
                }
            }
        }

        void renderer::onRenderEnd()
        {
            
        }
    }
}